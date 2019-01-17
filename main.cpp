#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Nachricht {

private:
    const string  s;

public:
    Nachricht (const string & s) : s(s) {

    }
    string text () const {
        stringstream ss;
            ss << s ;
        return ss.str();
    }

};

struct Beobachter {

private:
    string const s;

public:
    virtual ~Beobachter () {}
    virtual void benachrichtigen (const Nachricht& nachricht) const = 0;
};

class BeobachterImpl: public Beobachter {

private:
    string name;

public:
    BeobachterImpl (const string & name): name(name) {

    }
    virtual void benachrichtigen (const Nachricht& nachricht) const {
        std:: cout << "empfaeng Nachricht: " << nachricht.text() <<std:: endl;
    }
};

class Subjekt {

private:
    vector<Beobachter*> beobachter;
public:
    void beobachterHinzufuegen(Beobachter &b) {
        beobachter.push_back(&b);
    }

    void alleBenachrichtungen(const Nachricht &nachricht) {
        for (auto b: beobachter) {
            b->benachrichtigen(nachricht);
        }
    }
};

int main() {

    Subjekt subjekt;                                // create a subjekt object
    BeobachterImpl b1 ("b1");                       // create a BeobachterImpl object with parameter string
    BeobachterImpl b2 ("b2");                       // create a BeobachterImpl object with parameter string

    subjekt.beobachterHinzufuegen(b1);
    subjekt.beobachterHinzufuegen(b2);
    Nachricht nachricht ("Hallo Beobachter");
    subjekt.alleBenachrichtungen(nachricht);
    return 0;
}
