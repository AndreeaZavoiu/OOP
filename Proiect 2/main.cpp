#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;
#define MIN 1000000000    // un milion, just in case :)

class Vehicule {
protected:
    float m_volum;       // volumul vehiculului
    float volumComenzi;  // volumul total al comenzilor dintr-un vehicul
    double m_x,m_y;      // coordonatele trb modif dupa cu ale destinatiei
    float m_viteza;
    float timpAsteptare; // timpul de livrare a comenzilor adunat pt fiecare vehicul in parte
    bool m_rece;

public:
    // Constructor parametrizat
    Vehicule(float mVolum, float volumComenzi, double mX, double mY, float mViteza,
             float timpAsteptare, bool mRece) : m_volum(mVolum), volumComenzi(volumComenzi),
                                                m_x(mX), m_y(mY), m_viteza(mViteza), timpAsteptare(timpAsteptare), m_rece(mRece) {};

    // Setters
    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }
    // Getters
    double getX() { return m_x; }
    double getY() { return m_y; }
    int getViteza(){ return m_viteza; }
    float getVolumMarfa() { return volumComenzi; }
    float getVolumVehicul() { return m_volum; }
    float getTimpAsteptare() { return timpAsteptare; }
    void setVehicul(Vehicule* v) {

    }
    // Destructor
    virtual ~Vehicule() {};
};

class Scuter: public Vehicule {
public:
    Scuter(float mVolum, float volumComenzi, double mX, double mY, float mViteza, float timpAsteptare, bool mRece)
            : Vehicule(mVolum, volumComenzi, mX, mY, mViteza, timpAsteptare, mRece)
            {
                m_viteza = 20;
            }

    // function override
    int getViteza(){ return m_viteza; } // adica return 20;
    float getVolumMarfa() { return volumComenzi; }
};

class Masina: public Vehicule {
public:
    Masina(float mVolum, float volumComenzi, double mX, double mY, float mViteza, float timpAsteptare, bool mRece)
            : Vehicule(mVolum, volumComenzi, mX, mY, mViteza, timpAsteptare, mRece)
    {
        m_viteza = 10; // km/s
    }

    int getViteza(){ return m_viteza; } // adica return 10;
    float getVolumMarfa() { return volumComenzi; }
};

class Duba: public Vehicule {
public:
    Duba(float mVolum, float volumComenzi, double mX, double mY, float mViteza, float timpAsteptare, bool mRece)
            : Vehicule(mVolum, volumComenzi, mX, mY, mViteza, timpAsteptare, mRece)
    {
        m_viteza = 5;
    }

    int getViteza(){ return m_viteza; } // adica return 5;
    float getVolumMarfa() { return volumComenzi; }
};

class DubaFrigorifica: public Duba {
public:
    DubaFrigorifica(float mVolum, float volumComenzi, double mX, double mY, float mViteza, float timpAsteptare, bool mRece)
            : Duba(mVolum, volumComenzi, mX, mY, mViteza, timpAsteptare, mRece)
    {
        bool m_rece = true;
    }

    float getVolumMarfa() { return volumComenzi; }
};

class Colet {};


class Comanda {
    // Conventie: o comanda poate avea un singur colet !
    double xCom, yCom; // coordonatele de livrare a comenzii
    float m_masa, m_volum;
    float m_timpLivrare;
    bool m_rece;
    Vehicule* vehicul; // polimorfism => vehicul = new Masina;

public:
    Comanda(double xCom, double yCom, float masa, float volum, float timpLivrare, bool rece, Vehicule *vehicul)
            : xCom(xCom), yCom(yCom), m_masa(masa), m_volum(volum), m_timpLivrare(timpLivrare), m_rece(rece),
              vehicul(vehicul) {}

    // Setters
    void setX(double x) { xCom = x; }
    void setY(double y) { yCom = y; }
    void setVehicul(Vehicule* vehiculAlocat) { vehicul = vehiculAlocat; }
    // Getters
    double getXCom() { return xCom; }
    double getYCom() { return yCom; }
    float getVolum() { return m_volum; }
    float getTimpLivrare() { return m_timpLivrare; }

};


int distanta_normala(Vehicule* v, Comanda c)
{
    return sqrt(pow(c.getXCom() - v->getX(), 2) + pow(c.getYCom() - v->getY(), 2));
}
int distanta_manhattan(Vehicule* v, Comanda c)
{
    return abs(c.getXCom() - v->getX()) + abs(c.getYCom() - v->getY());
}

bool areSpatiu (Vehicule* v, Comanda c) {
    return v->getVolumMarfa() + c.getVolum() < v->getVolumVehicul(); // volumul coletelor din masina plus volumul coletului din discutie sa nu depaseasca volumul vehiculului
}

bool livreazaLaTimp (Vehicule* v, Comanda c, float timp){
    return timp + v->getTimpAsteptare() < c.getTimpLivrare();
}

Vehicule* alocaVehicul(Comanda c, vector<Vehicule*> vehicule, int strategie)
{
    float distanta, timp, volumMarfa, dMin = MIN, tMin = MIN, vMin = MIN;
    int indexDmin, indexTmin, indexVmin;

    for(int i = 0; i < vehicule.size(); i++)
    {
        Scuter *s = dynamic_cast<Scuter*>(vehicule[i]); // functioneaza pt vehicule[0] de exemplu

        // Calculez distanta de la vehicul la colet, timpul de ajungere a vehiculului la colet si volumul creat in vehicul prin adaugarea coletului,
        // in functie de tipul vehiculului :

        if (s)      // vehiculul e scuter => linie dreapta -> distanta normala
        {
            distanta = distanta_normala(vehicule[i], c);
            timp = distanta / s->getViteza(); // v=d/t  =>  t=d/v
            volumMarfa = s->getVolumMarfa() + c.getVolum();
        }
        else       // altfel e masina/duba  => distanta_manhattan |x2-x1| + |y2-y1|
        {
            distanta = distanta_manhattan(vehicule[i], c);
            timp = distanta / vehicule[i]->getViteza();
            volumMarfa = vehicule[i]->getVolumMarfa() + c.getVolum();
        }


        // Actualizez pentru fiecare strategie care vehicul e cel mai potrivit
        // dupa ce am verificat ca e spatiu in vehiculul curent cu care compar si ca ar livra comanda la timp :

        if ( areSpatiu (vehicule[i], c) && livreazaLaTimp (vehicule[i], c, timp) )
        {
            // strategia 1: vehiculul cel mai apropiat de client, i.e. distanta minima
            if (distanta < dMin) {
                dMin = distanta;
                indexDmin = i;
            }
            // strategia 2: vehiculul care poate livra cel mai repede coletul, i.e. timp minim
            if (timp < tMin) {
                dMin = distanta;
                indexTmin = i;
            }
            // strategia 3: vehiculul cel mai putin incarcat, i.e. volum minim
            if (volumMarfa < vMin) {
                dMin = distanta;
                indexVmin = i;
            }
        }
    }

    // Cele 3 strategii de alocare a coletelor pe care le poate aplica firma:
    // Obs: daca pentru vreo comanda dMin, tMin sau vMin raman MIN, atunci clientul este refuzat
    if (strategie == 1 && dMin < MIN)
        return vehicule[indexDmin];             // return Vehicul cu distanta minima
    else if (strategie == 2 && tMin < MIN)
        return vehicule[indexTmin];             // vehicul cu timp minim pana la comanda
    else if (strategie==3 && vMin < MIN)
        return vehicule[indexVmin];             // vehicul cu volum minim de marfa in el
    else return nullptr;                        // clientul va fi refuzat
}


// Interfata = clasa abstracta care are cel putin o functie virtuala pura (initializata cu 0), de ex: void ceva() = 0;
class Firma {
private: // nu vreau sa fie vazute de clasa derivata
    vector<Vehicule*> vehicule;
    vector<Comanda*> comenzi;
protected: // vreau sa fie vazute de clasa derivata
    string m_oras;
public:
    virtual int arataAngajatii() = 0;
    virtual ~Firma() {}
};

class Sofer: public Firma {
    string m_nume;
    Vehicule* v;
    vector<Comanda*> c;
public:
    void setNume(string nume) { m_nume = nume; }
    int arataAngajatii() { cout<<m_nume<<" "; }
    virtual ~Sofer() {}
};

int main()
{
    vector<Vehicule*> vehicule = {};

    int nrVehicule, nrMasini, nrScutere, nrDube, nrDubeFrig;
    cout<< "\nNumarul total al vehiculelor: ";
    cin>> nrVehicule;
    cout<< "\nNumarul masinilor: ";
    cin>> nrMasini;
    cout<< "\nNumarul scuterelor: ";
    cin>> nrScutere;
    cout<< "\nNumarul dubelor: "; // fara cele frigorifice
    cin>> nrDube;
    cout<< "\nNumarul dubelor frigorifice: ";
    cin>> nrDubeFrig;

    float masa,volum, timpLivrare;
    double x,y;
    for (int i=0; i < nrMasini; i++) {
        cout<<"\nMasa, volumul si coordonatele initiale ale masinii "<<i+1<<": ";
        cin>>masa>>volum>>x>>y;
    }
    for (int i=0; i < nrScutere; i++){
        cout<<"\nMasa, volumul si coordonatele initiale ale scuterului "<<i+1<<": ";
        cin>>masa>>volum>>x>>y;
    }
    for (int i=0; i < nrDube; i++){
        cout<<"\nMasa, volumul si coordonatele initiale ale dubei "<<i+1<<": ";
        cin>>masa>>volum>>x>>y;
    }
    for (int i=0; i < nrDubeFrig; i++){
        cout<<"\nMasa, volumul si coordonatele initiale ale dubei frigorifice "<<i+1<<": ";
        cin>>masa>>volum>>x>>y;
    }

    int nrComenzi;
    cout<<"\nNumarul comenzilor: ";
    cin >> nrComenzi;
    vector<Comanda*> comenzi = {};
    bool rece;
    for(int i = 0; i < nrComenzi; i++) // se citesc n comenzi
    {
        cout<<"\nDatele comenzii "<<i+1<<" (coordonate, masa, volum, timpLivrare): ";
        cin>>x>>y>>masa>>volum>>timpLivrare;
        cout<<"\nDaca doriti o comanda rece, tastati 1, altfel tastati 0: ";
        cin>>rece;
        Comanda *c = new Comanda(x, y, masa, volum, timpLivrare, rece, vehicule[i]);
        comenzi.push_back(c);

        cout<<"\nStrategia de alocare a coletului: ";
        int strategie;
        cin >> strategie;

        Vehicule* vehiculAlocat = alocaVehicul(*c, vehicule, strategie);
        c->setVehicul(vehiculAlocat);
        // Obs: dupa livrare, coordonatele vehicului devin coordonatele comenzii la care a livrat
        vehiculAlocat->setX( c->getXCom() );
        vehiculAlocat->setY( c->getYCom() );
    }

    return 0;
}


// Exemple:

// vector<Vehicule*> vehicule = {new Scuter, new Masina, new Duba, new DubaFrigorifica}; // dynamic cast => e scuter nu vehicul
// vehicule.push_back(new Masina); // pe vehicule[4] si pe vehicule[1] sunt masini