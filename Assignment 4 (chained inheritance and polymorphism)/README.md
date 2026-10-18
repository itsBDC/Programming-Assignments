# C++ Take-Home Assignment: Chained Inheritance and Polymorphism

| File | Topic | Example used |
|------|-------|--------------|
| `chained_inheritance.cpp` | Chained (multilevel) inheritance | `Device` → `Sensor` → `TemperatureSensor` |
| `polymorphism.cpp` | Runtime polymorphism | `Payment` → `MobileMoneyPayment`, `CardPayment`, `CashPayment` |

Both examples model relationships between **programming/system concepts** (devices, sensors, payment methods), not human family relationships.

---

## How to compile and run

You need a C++ compiler such as g++ (MinGW-w64/MSYS2 on Windows, or g++ on Linux/macOS).

```bash
g++ -std=c++11 -Wall -Wextra chained_inheritance.cpp -o chained
./chained            # Windows: chained.exe

g++ -std=c++11 -Wall -Wextra polymorphism.cpp -o poly
./poly               # Windows: poly.exe
```

---

# Part 1: Chained (Multilevel) Inheritance

## The idea

**Inheritance** lets a new class (the *derived* class) reuse the data and functions of an existing class (the *base* class) instead of rewriting them.

**Chained (multilevel) inheritance** means the classes form a chain: a class inherits from a parent, and that parent itself inherits from another class.

```
   Device              Level 1  (base class)
     ▲
     │  is-a
   Sensor              Level 2  (derived from Device, parent of TemperatureSensor)
     ▲
     │  is-a
   TemperatureSensor   Level 3  (derived from Sensor)
```

A `TemperatureSensor` **is a** `Sensor`, and a `Sensor` **is a** `Device`. This "is-a" test is what makes inheritance a sensible choice. Each level adds something more specific.

## What each class contains

| Class | Inherits from | Data members | Member functions |
|-------|---------------|--------------|------------------|
| `Device` | nothing | `deviceId`, `location`, `powered` | `powerOn()`, `powerOff()`, `isPoweredOn()`, `showDeviceInfo()` |
| `Sensor` | `Device` | `unit`, `lastReading` | `recordReading()`, `getLastReading()`, `showSensorInfo()` |
| `TemperatureSensor` | `Sensor` | `maxSafeTemp` | `isOverheating()`, `toFahrenheit()`, `showStatus()` |

So a `TemperatureSensor` object really contains **all** of these members: its own, plus everything from `Sensor` and `Device`.

## How it works

**1. The `: public` syntax creates the chain.**

```cpp
class Sensor : public Device { ... };
class TemperatureSensor : public Sensor { ... };
```

**2. `protected` members are shared down the chain.**
`deviceId`, `location` and `powered` are `protected` in `Device`. That means `Sensor` and `TemperatureSensor` can use them directly, but code in `main()` cannot. This protects the data while still allowing inheritance. For example, `Sensor::recordReading()` checks `powered`, a variable it never declared itself.

**3. Constructors run top-down, destructors run bottom-up.**
When a `TemperatureSensor` is created, C++ builds the base part first. The derived class passes values up using an initialiser list:

```cpp
TemperatureSensor(...) : Sensor(id, loc, "degC"), maxSafeTemp(maxTemp) { ... }
Sensor(...)            : Device(id, loc), unit(...), lastReading(0.0)  { ... }
```

Order of construction: `Device` → `Sensor` → `TemperatureSensor`.
Order of destruction is the reverse: `TemperatureSensor` → `Sensor` → `Device`.
You can see this in the program output.

**4. A derived-class object can use members from every level above it.**

```cpp
serverRoom.powerOn();          // defined in Device         (Level 1)
serverRoom.recordReading(28.5);// defined in Sensor         (Level 2)
serverRoom.isOverheating();    // defined in TemperatureSensor (Level 3)
```

**5. Inheritance only goes one way.**
A plain `Sensor` object (the `humidity` object in `main`) has `Device` and `Sensor` members, but not `isOverheating()`, because that belongs to the class *below* it. The line is left commented out in the code because it would not compile.

## What `main()` demonstrates

1. Creating a `TemperatureSensor` and watching the constructor order.
2. Using inherited `Device` members (`powerOn`).
3. Using inherited `Sensor` members (`recordReading`).
4. Using members local to `TemperatureSensor` (`showStatus`, `isOverheating`).
5. Powering off and showing that the rule in `Sensor` still depends on the state stored in `Device`.
6. Creating a standalone `Sensor` object (a Level 2 object).
7. Objects being destroyed in reverse order.

## Sample output (abridged)

```
=== 1. Creating a TemperatureSensor (watch the constructor order) ===
  [Device]            constructor ran for TS-01
  [Sensor]            constructor ran for TS-01
  [TemperatureSensor] constructor ran for TS-01

=== 2. Using members inherited from Device (Level 1) ===
TS-01: cannot record, sensor is OFF
TS-01 powered ON

=== 3. Using members inherited from Sensor (Level 2) ===
TS-01 recorded 28.5 degC

=== 4. Using members defined in TemperatureSensor (Level 3) ===
Device ID : TS-01
Location  : Server Room
Power     : ON
Unit      : degC
Last read : 28.5 degC
Max safe  : 35 degC
In degF   : 83.3
Status    : Normal

--- Temperature rises ---
TS-01 recorded 38.2 degC
...
Status    : WARNING - OVERHEATING!

=== 7. End of main: objects are destroyed in reverse order ===
  [Sensor]            destructor ran for HS-01
  [Device]            destructor ran for HS-01
  [TemperatureSensor] destructor ran for TS-01
  [Sensor]            destructor ran for TS-01
  [Device]            destructor ran for TS-01
```

---

# Part 2: Polymorphism

## The idea

**Polymorphism** means "many forms": the *same function call* behaves *differently* depending on the object it is used on.

In this program the checkout only needs to say "pay this amount". It does not care whether the customer is using Mobile Money, a card or cash. The correct behaviour is chosen **while the program is running** (*runtime polymorphism*, also called dynamic binding).

```
                  Payment                 ← parent: virtual pay(), virtual calculateFee()
                 ▲   ▲   ▲
        ┌────────┘   │   └─────────┐
 MobileMoneyPayment  CardPayment   CashPayment    ← each overrides pay()
```

## What each class contains

| Class | Extra data | `calculateFee()` | `pay()` behaviour |
|-------|-----------|------------------|-------------------|
| `Payment` (parent) | `payerName` | returns 0 | generic message |
| `MobileMoneyPayment` | `phoneNumber` | overridden: 1% | sends a PIN prompt to the phone |
| `CardPayment` | `last4Digits` | overridden: 2.5% | contacts the bank for authorisation |
| `CashPayment` | `amountTendered` | **not** overridden (uses the parent's 0) | checks the cash, computes change |

The fee rates are made-up numbers for demonstration only.

## How it works

**1. `virtual` marks a function as "can be replaced by derived classes".**

```cpp
virtual void pay(double amount) { ... }       // in Payment
```

**2. Derived classes override it** with the same signature. The `override` keyword asks the compiler to check that you really are overriding something, which catches typos.

```cpp
void pay(double amount) override { ... }      // in MobileMoneyPayment
```

**3. A base-class pointer (or reference) can point to any derived object.**

```cpp
Payment* ptr = &momo;     // a Payment pointer holding a MobileMoneyPayment
ptr->pay(50000);          // runs MobileMoneyPayment::pay
ptr = &card;
ptr->pay(50000);          // same line, now runs CardPayment::pay
```

**4. The decision happens at run time.** C++ looks at the *actual object* the pointer refers to (using a hidden table of function addresses called the *vtable*), not at the pointer's declared type. That is why the same line `ptr->pay(50000)` produces three different results.

**5. Virtual destructor.** `Payment` has `virtual ~Payment()`. This is good practice whenever a class has virtual functions, so that deleting a derived object through a base pointer cleans up correctly.

**6. Not overriding is allowed.** `CashPayment` does not override `calculateFee()`, so it inherits the parent's version (fee = 0).

**7. Contrast with a non-virtual function.** `describe()` is *not* virtual. Called through a `Payment*`, it always runs the **parent's** version, even if the pointer holds a `MobileMoneyPayment`. This shows that `virtual` is what makes the behaviour polymorphic.

## What `main()` demonstrates

1. **One base pointer, three behaviours.** The same `ptr->pay(50000)` is called with a pointer to each object.
2. **Array of base pointers.** A loop calls `calculateFee(120000)` on each; the three fees differ.
3. **Base reference as a parameter.** `checkout(Payment& method, double amount)` works for any payment type.
4. **Non-virtual contrast.** Shows what happens *without* `virtual`.

## Sample output

```
=== 1. One base-class pointer, three different behaviours ===
[Mobile Money] Prompt sent to 0772 000 111. Amina enters PIN to approve.
               Amount: UGX 50000 | Fee: UGX 500 | Total: UGX 50500

[Card] Card ending 4821 inserted. Contacting bank for authorisation...
       Amount: UGX 50000 | Fee: UGX 1250 | Total: UGX 51250

[Cash] Carol hands over UGX 60000.
       Amount: UGX 50000 | Fee: UGX 0 | Change: UGX 10000

=== 2. Array of base-class pointers: same call, loop over objects ===
Fee on UGX 120000 = UGX 1200
Fee on UGX 120000 = UGX 3000
Fee on UGX 120000 = UGX 0

=== 3. Base-class reference as a function parameter ===
Checkout -> [Mobile Money] Prompt sent to 0772 000 111. Amina enters PIN to approve.
               Amount: UGX 20000 | Fee: UGX 200 | Total: UGX 20200
Checkout -> [Card] Card ending 4821 inserted. Contacting bank for authorisation...
       Amount: UGX 20000 | Fee: UGX 500 | Total: UGX 20500
Checkout -> [Cash] Carol hands over UGX 60000.
       Not enough cash! Short by UGX 20000

=== 4. Contrast: non-virtual function does NOT behave polymorphically ===
[Payment::describe] a payment method owned by Amina
[MobileMoneyPayment::describe] Mobile Money wallet 0772 000 111
```




## Key terms

| Term | Meaning |
|------|---------|
| Base / parent class | The class being inherited from |
| Derived / child class | The class that inherits |
| Chained (multilevel) inheritance | A → B → C, where C derives from B and B derives from A |
| `protected` | Accessible inside the class and its derived classes, but not from outside |
| `virtual` function | A function that derived classes may override, resolved at run time |
| `override` | Tells the compiler this function replaces a virtual function of the base class |
| Runtime polymorphism | Same call, different behaviour, chosen by the actual object type while the program runs |
| Dynamic binding | Another name for resolving the function call at run time |
