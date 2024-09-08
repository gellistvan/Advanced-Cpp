#include <iostream>
#include <unordered_map>
#include <memory>
#include <stdexcept>

// Account data storage (for simplicity)
std::unordered_map<std::string, double> accounts;

// Command base class
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

// CreateAccountCommand
class CreateAccountCommand : public Command {
public:
    CreateAccountCommand(const std::string& accountId) : accountId(accountId) {}
    void execute() override {
        // Logic to create an account
        std::cout << "Creating account: " << accountId << std::endl;
        if (accounts.find(accountId) != accounts.end()) {
            throw std::runtime_error("Account already exists");
        }
        accounts[accountId] = 0.0;
    }

private:
    std::string accountId;
};

// DepositMoneyCommand
class DepositMoneyCommand : public Command {
public:
    DepositMoneyCommand(const std::string& accountId, double amount) 
        : accountId(accountId), amount(amount) {}
    void execute() override {
        // Logic to deposit money
        std::cout << "Depositing " << amount << " to account: " << accountId << std::endl;
        if (accounts.find(accountId) == accounts.end()) {
            throw std::runtime_error("Account does not exist");
        }
        accounts[accountId] += amount;
    }

private:
    std::string accountId;
    double amount;
};


// Query base class
class Query {
public:
    virtual ~Query() = default;
    virtual void execute() const = 0;
};

// GetAccountBalanceQuery
class GetAccountBalanceQuery : public Query {
public:
    GetAccountBalanceQuery(const std::string& accountId) : accountId(accountId) {}
    void execute() const override {
        // Logic to get account balance
        std::cout << "Getting balance for account: " << accountId << std::endl;
        if (accounts.find(accountId) == accounts.end()) {
            throw std::runtime_error("Account does not exist");
        }
        std::cout << "Account balance: " << accounts.at(accountId) << std::endl;
    }

private:
    std::string accountId;
};

class CommandHandler {
public:
    void handle(const std::shared_ptr<Command>& command) {
        command->execute();
    }
};

class QueryHandler {
public:
    void handle(const std::shared_ptr<Query>& query) const {
        query->execute();
    }
};

int main() {
    CommandHandler commandHandler;
    QueryHandler queryHandler;

    // Creating an account
    std::shared_ptr<Command> createAccountCmd = std::make_shared<CreateAccountCommand>("12345");
    commandHandler.handle(createAccountCmd);

    // Depositing money
    std::shared_ptr<Command> depositMoneyCmd = std::make_shared<DepositMoneyCommand>("12345", 100.0);
    commandHandler.handle(depositMoneyCmd);

    // Getting account balance
    std::shared_ptr<Query> getBalanceQuery = std::make_shared<GetAccountBalanceQuery>("12345");
    queryHandler.handle(getBalanceQuery);

    return 0;
}
