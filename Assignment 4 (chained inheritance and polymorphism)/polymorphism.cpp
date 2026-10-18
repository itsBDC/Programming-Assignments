#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Payment {
protected:
    string payerName;

public:
    Payment(const string& name) : payerName(name) {}

    
    virtual ~Payment() {}

   
    virtual double calculateFee(double amount) const {
        (void)amount;           
        return 0.0;
    }

    virtual void pay(double amount) {
        cout << payerName << " makes a generic payment of UGX " << amount << endl;
    }


    void describe() const {
        cout << "[Payment::describe] a payment method owned by " << payerName << endl;
    }
};


class MobileMoneyPayment : public Payment {
private:
    string phoneNumber;

public:
    MobileMoneyPayment(const string& name, const string& phone)
        : Payment(name), phoneNumber(phone) {}

    double calculateFee(double amount) const override {
        return amount * 0.01;                   // 1% fee
    }

    void pay(double amount) override {
        double fee = calculateFee(amount);
        cout << "[Mobile Money] Prompt sent to " << phoneNumber
             << ". " << payerName << " enters PIN to approve." << endl;
        cout << "               Amount: UGX " << amount
             << " | Fee: UGX " << fee
             << " | Total: UGX " << amount + fee << endl;
    }

    void describe() const 
    {                    
        cout << "[MobileMoneyPayment::describe] Mobile Money wallet " << phoneNumber << endl;
    }
};


class CardPayment : public Payment {
private:
    string last4Digits;

public:
    CardPayment(const string& name, const string& last4)
        : Payment(name), last4Digits(last4) {}

    double calculateFee(double amount) const override {
        return amount * 0.025;                  // 2.5% fee
    }

    void pay(double amount) override 
    {
        double fee = calculateFee(amount);
        cout << "[Card] Card ending " << last4Digits
             << " inserted. Contacting bank for authorisation..." << endl;
        cout << "       Amount: UGX " << amount
             << " | Fee: UGX " << fee
             << " | Total: UGX " << amount + fee << endl;
    }
};

class CashPayment : public Payment {
private:
    double amountTendered;

public:
    CashPayment(const string& name, double tendered)
        : Payment(name), amountTendered(tendered) {}


    void pay(double amount) override 
    {
        cout << "[Cash] " << payerName << " hands over UGX " << amountTendered << "." << endl;
        if (amountTendered >= amount) {
            cout << "       Amount: UGX " << amount
                 << " | Fee: UGX " << calculateFee(amount)
                 << " | Change: UGX " << amountTendered - amount << endl;
        } else {
            cout << "       Not enough cash! Short by UGX " << amount - amountTendered << endl;
        }
    }
};


void checkout(Payment& method, double amount) {
    cout << "Checkout -> ";
    method.pay(amount);        
}

int main() {
    cout << fixed << setprecision(0);

    MobileMoneyPayment momo("Amina", "0772 000 111");
    CardPayment        card("Brian", "4821");
    CashPayment        cash("Carol", 60000);

    cout << "=== 1. One base-class pointer, three different behaviours ===" << endl;
    Payment* ptr = nullptr;

    ptr = &momo;
    ptr->pay(50000);
    cout << endl;

    ptr = &card;
    ptr->pay(50000);
    cout << endl;

    ptr = &cash;
    ptr->pay(50000);

    cout << "\n=== 2. Array of base-class pointers: same call, loop over objects ===" << endl;
    Payment* methods[] = { &momo, &card, &cash };
    for (Payment* m : methods) {
        cout << "Fee on UGX 120000 = UGX " << m->calculateFee(120000) << endl;
    }

    cout << "\n=== 3. Base-class reference as a function parameter ===" << endl;
    checkout(momo, 20000);
    checkout(card, 20000);
    checkout(cash, 80000);     
    cout << "\n=== 4. Contrast: non-virtual function does NOT behave polymorphically ===" << endl;
    ptr = &momo;
    ptr->describe();            
    momo.describe();            

    return 0;
}
