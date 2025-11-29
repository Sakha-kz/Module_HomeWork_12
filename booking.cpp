#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <mutex>
#include <random>
#include <atomic>

using namespace std::chrono_literals;

struct Slot {
    std::string date;
    std::string venue;
    bool reserved = false;
    std::string reservedBy;
};


class PaymentGateway {
public:
    bool charge(double amount, int attempt = 1) {
        static std::mt19937 rng((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(1, 100);
        int v = dist(rng);
        bool success = (v <= 70);
        // имитируем задержку сети
        std::this_thread::sleep_for(300ms);
        std::cout << "[PaymentGateway] Attempt " << attempt << " -> " << (success ? "SUCCESS" : "FAIL") << "\n";
        return success;
    }
};


class Contractor {
    std::string name;
public:
    Contractor(std::string n): name(std::move(n)) {}
    void notifyAndConfirm(const std::string &task, std::atomic<int> &confirmations, int id) {
        static std::mt19937 rng((unsigned)std::hash<std::string>{}(name) ^ id);
        std::uniform_int_distribution<int> d(100, 800);
        int ms = d(rng);
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        std::cout << "[Contractor " << name << "] confirmed task: " << task << " (delay " << ms << "ms)\n";
        ++confirmations;
    }
    std::string getName() const { return name; }
};


class VenueAdmin {
    std::string name;
public:
    VenueAdmin(std::string n): name(std::move(n)) {}
    void notifyBooking(const std::string &bookingId) {
        std::cout << "[VenueAdmin " << name << "] Notified about booking " << bookingId << "\n";
    }
    void createTasksAndNotifyContractors(const std::string &bookingId,
                const std::vector<Contractor> &contractors) {

        std::string task = "Prepare venue for booking " + bookingId;
        std::cout << "[VenueAdmin] Creating task list: " << task << "\n";

        std::atomic<int> confirmations{0};
        std::vector<std::thread> threads;
        int id = 1;
        for (auto &c : contractors) {
            threads.emplace_back(&Contractor::notifyAndConfirm, &const_cast<Contractor&>(c), task, std::ref(confirmations), id++);
        }
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start < 3s) {
            if ((int)confirmations == (int)contractors.size()) break;
            std::this_thread::sleep_for(100ms);
        }
        for (auto &t : threads) if (t.joinable()) t.join();

        std::cout << "[VenueAdmin] Confirmations received: " << confirmations << " / " << contractors.size() << "\n";
    }
};


class BookingSystem {
    std::vector<Slot> slots;
    std::mutex mtx;
    PaymentGateway payment;
    VenueAdmin admin;
    std::vector<Contractor> contractors;

public:
    BookingSystem(): admin("Alice") {
        slots.push_back({"2025-12-01", "GrandHall", false, ""});
        slots.push_back({"2025-12-02", "GrandHall", false, ""});
        slots.push_back({"2025-12-01", "SmallRoom", false, ""});

        contractors.emplace_back("Decor");
        contractors.emplace_back("Catering");
        contractors.emplace_back("AV");
    }

    bool checkAvailability(const std::string &date, const std::string &venue) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto &s : slots) {
            if (s.date == date && s.venue == venue && !s.reserved) return true;
        }
        return false;
    }

    bool reserveTemporary(const std::string &bookingId, const std::string &date, const std::string &venue) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto &s : slots) {
            if (s.date == date && s.venue == venue && !s.reserved) {
                s.reserved = true;
                s.reservedBy = bookingId;
                std::cout << "[BookingSystem] Temporarily reserved slot " << venue << " " << date << " for " << bookingId << "\n";
                return true;
            }
        }
        return false;
    }

    void releaseTemporary(const std::string &bookingId) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto &s : slots) {
            if (s.reserved && s.reservedBy == bookingId) {
                s.reserved = false;
                s.reservedBy.clear();
                std::cout << "[BookingSystem] Released temporary reservation for " << bookingId << "\n";
            }
        }
    }


    void confirmBooking(const std::string &bookingId) {
        std::cout << "[BookingSystem] Booking " << bookingId << " confirmed. Persisting to DB (simulated).\n";
    }


    bool processBooking(const std::string &bookingId, const std::string &date, const std::string &venue,
                        double amount, int paymentAttempts = 3) {

        std::cout << "---- New booking request: " << bookingId << " (" << venue << " " << date << ") ----\n";

        if (!checkAvailability(date, venue)) {
            std::cout << "[System] NOT available. Suggest other dates.\n";
            return false;
        }


        if (!reserveTemporary(bookingId, date, venue)) {
            std::cout << "[System] Failed to reserve temporarily.\n";
            return false;
        }


        bool paid = false;
        for (int attempt = 1; attempt <= paymentAttempts; ++attempt) {
            std::cout << "[System] Charging payment attempt " << attempt << " (amount " << amount << ")\n";
            if (payment.charge(amount, attempt)) { paid = true; break; }

            std::this_thread::sleep_for(std::chrono::milliseconds(300 * attempt));
        }

        if (!paid) {
            std::cout << "[System] Payment failed after " << paymentAttempts << " attempts. Releasing slot and notifying client.\n";
            releaseTemporary(bookingId);
            return false;
        }


        confirmBooking(bookingId);
        admin.notifyBooking(bookingId);


        admin.createTasksAndNotifyContractors(bookingId, contractors);


        std::cout << "[System] Post-event report scheduled for manager.\n";

        return true;
    }
};

int main() {
    BookingSystem system;

    // Пример: 3 брони — последовательно
    struct Request { std::string id, date, venue; double amount; };
    std::vector<Request> reqs = {
        {"BKG-1001", "2025-12-01", "GrandHall", 1500.0},
        {"BKG-1002", "2025-12-01", "GrandHall", 1500.0}, // тот же слот, должен быть уже занят
        {"BKG-1003", "2025-12-02", "GrandHall", 900.0}
    };

    for (auto &r: reqs) {
        bool ok = system.processBooking(r.id, r.date, r.venue, r.amount, 3);
        std::cout << "Booking " << r.id << " result: " << (ok ? "CONFIRMED" : "FAILED") << "\n\n";
        // краткая пауза между запросами
        std::this_thread::sleep_for(200ms);
    }

    std::cout << "All requests processed.\n";
    return 0;
}