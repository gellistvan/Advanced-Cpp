#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Event {
public:
    virtual ~Event() = default;
    virtual std::string getName() const = 0;
};

class AccountCreatedEvent : public Event {
public:
    AccountCreatedEvent(const std::string& accountId) : accountId(accountId) {}
    std::string getName() const override { return "AccountCreatedEvent"; }
    std::string getAccountId() const { return accountId; }

private:
    std::string accountId;
};

class MoneyDepositedEvent : public Event {
public:
    MoneyDepositedEvent(const std::string& accountId, double amount) 
        : accountId(accountId), amount(amount) {}
    std::string getName() const override { return "MoneyDepositedEvent"; }
    std::string getAccountId() const { return accountId; }
    double getAmount() const { return amount; }

private:
    std::string accountId;
    double amount;
};

class EventStore {
public:
    void saveEvent(const std::shared_ptr<Event>& event) {
        events.push_back(event);
    }

    const std::vector<std::shared_ptr<Event>>& getEvents() const {
        return events;
    }

private:
    std::vector<std::shared_ptr<Event>> events;
};

class BankAccount {
public:
    BankAccount(const std::string& id) : id(id), balance(0) {}

    void createAccount() {
        applyEvent(std::make_shared<AccountCreatedEvent>(id));
    }

    void depositMoney(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Amount must be positive");
        }
        applyEvent(std::make_shared<MoneyDepositedEvent>(id, amount));
    }

    void applyEvent(const std::shared_ptr<Event>& event) {
        if (auto e = std::dynamic_pointer_cast<AccountCreatedEvent>(event)) {
            apply(*e);
        } else if (auto e = std::dynamic_pointer_cast<MoneyDepositedEvent>(event)) {
            apply(*e);
        }
        eventStore.saveEvent(event);
    }

    void replayEvents() {
        for (const auto& event : eventStore.getEvents()) {
            if (auto e = std::dynamic_pointer_cast<AccountCreatedEvent>(event)) {
                apply(*e);
            } else if (auto e = std::dynamic_pointer_cast<MoneyDepositedEvent>(event)) {
                apply(*e);
            }
        }
    }

    double getBalance() const {
        return balance;
    }

private:
    void apply(const AccountCreatedEvent&) {
        // Nothing to do for account creation in this simple example
    }

    void apply(const MoneyDepositedEvent& event) {
        balance += event.getAmount();
    }

    std::string id;
    double balance;
    EventStore eventStore;
};

int main() {
    BankAccount account("12345");
    account.createAccount();
    account.depositMoney(100);
    account.depositMoney(50);

    std::cout << "Current balance: " << account.getBalance() << std::endl;

    // Simulate a system restart by creating a new aggregate and replaying events
    BankAccount restoredAccount("12345");
    restoredAccount.replayEvents();

    std::cout << "Restored balance: " << restoredAccount.getBalance() << std::endl;

    return 0;
}

