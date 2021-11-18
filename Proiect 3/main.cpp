/*
        Zavoiu Andreea Stefania - 152
        Tutore laborator: Deaconu Stefan
        MinGW - w64 6.0
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Malware {
public:
    Malware();
    Malware(double rating, const string &data, const string &nume, const string &metodaInfectare,
            const vector<string> &registri) : m_rating(rating), m_data(data), m_nume(nume),
                    m_registri(registri) {
        if (metodaInfectare != "")  m_metodaInfectare = metodaInfectare;
        else  m_metodaInfectare = "unknown";
    }
    Malware(const Malware& m);
    virtual Malware& operator= (Malware m);
    virtual ~Malware(){}
    friend istream& operator>> (istream& in, Malware& m);
    friend ostream& operator<< (ostream& out, Malware& m);

protected:
    double m_rating;
    string m_data;
    string m_nume;
    string m_metodaInfectare;
    vector<string> m_registri;

};
Malware::Malware(const Malware &m) {
    m_rating = m.m_rating;
    m_data = m.m_data;
    m_nume = m.m_nume;
    m_metodaInfectare = m.m_metodaInfectare;
    for (int i=0; i<m.m_registri.size(); i++)
        m_registri.push_back(m.m_registri[i]);
}
Malware& Malware::operator= (Malware m){
    m_rating = m.m_rating;
    m_data = m.m_data;
    m_nume = m.m_nume;
    m_metodaInfectare = m.m_metodaInfectare;
    for (int i=0; i<m.m_registri.size(); i++)
        m_registri.push_back(m.m_registri[i]);
    return *this;
}
Malware::Malware(){
    m_rating=0;
    m_data = m_nume = "";
    m_metodaInfectare = "unknown";
    m_registri = {};
}
istream& operator>> (istream& in, Malware& m){
    cout << "Introduceti ratingul impactului:\n";
    in >> m.m_rating;
    cout << "Introduceti data de infectare:\n";
    in >> m.m_data;
    cout << "Introduceti numele Malware-ului:\n";
    in >> m.m_nume;
    cout << "Introduceti metoda de infectare:\n";
    in >> m.m_metodaInfectare;
    cout << "Introduceti un numarul diferit de 0 pentru fiecare registru modificat pe care vreti sa il cititi, apoi registrul, si tastati 0 cand ati terminat:\n";
    int counter=1; string x;
    while (counter != 0) {
        cin >> counter;
        if (counter ) {
            in >> x;
            m.m_registri.push_back(x);
    } }
    return in;
}
ostream& operator<< (ostream& out, Malware& m){
    out << "Ratingul impactului :" << m.m_rating;
    out << ", data de infectare: " << m.m_data;
    out << ", numele Malware-ului: " << m.m_nume;
    out << ", metoda de infectare: " << m.m_metodaInfectare;
    for (int i=0; i<m.m_registri.size(); i++)
        out << ", registrul " << i+1 << m.m_registri[i];
    cout << endl;
    return out;
}



class Rootkit : public Malware {
public:
    Rootkit();
    Rootkit(double rating, const string &data, const string &nume, const string &metodaInfectare,
            const vector<string> &registri, const vector<string> &listaImporturi, const vector<string> &listaStringuri);
    virtual ~Rootkit(){}
    Rootkit (const Rootkit& m);
    virtual Rootkit& operator=(Rootkit m);
    bool rootkitRating(Rootkit& m);
    friend istream& operator>> (istream& in, Rootkit& m);
    friend ostream& operator<< (ostream& out, Rootkit& m);

protected:
    vector<string> m_listaImporturi;
    vector<string> m_listaStringuri;
};
bool Rootkit::rootkitRating(Rootkit &m) {
    for (int i=0; i<m.m_listaStringuri.size(); i++) {
        auto x = m.m_listaStringuri[i];
        if (x == "SSDT" || x == "System Service Descriptor Table" || x == "NtCreateFile")
            return 1;
    }
    return 0;
}
Rootkit::Rootkit(const Rootkit &m) {
    for (int i=0; i<m.m_listaImporturi.size(); i++)
        m_listaImporturi.push_back(m.m_listaImporturi[i]);

    for (int i=0; i<m.m_listaStringuri.size(); i++)
       m_listaStringuri.push_back(m.m_listaStringuri[i]);
}
Rootkit& Rootkit::operator=(Rootkit m){
    for (int i=0; i<m.m_listaImporturi.size(); i++)
        m_listaImporturi.push_back(m.m_listaImporturi[i]);

    if (m.rootkitRating(m))
        m_rating += 100;

    for (int i=0; i<m.m_listaStringuri.size(); i++)
        m_listaStringuri.push_back(m.m_listaStringuri[i]);
    return *this;
}
Rootkit::Rootkit() : Malware() {
    m_listaImporturi = {};
    m_listaStringuri = {};
}
Rootkit::Rootkit(double rating, const string &data, const string &nume, const string &metodaInfectare,
                 const vector<string> &registri, const vector<string> &listaImporturi,
                 const vector<string> &listaStringuri) : Malware(rating, data, nume, metodaInfectare, registri),
                 m_listaImporturi(listaImporturi), m_listaStringuri(listaStringuri) {}

istream& operator>> (istream& in, Rootkit& m){
    cin >> static_cast<Malware&>(m);
    cout << "Introduceti lista de importuri:\n";
    cout << "Introduceti un numarul diferit de 0 pentru fiecare import pe care vreti sa il cititi, apoi importul, si tastati 0 cand ati terminat:\n";
    int counter=1; string x;
    while (counter != 0) {
        cin >> counter;
        if (counter ) {
            in >> x;
            m.m_listaImporturi.push_back(x);
        } }
    cout << "Introduceti lista de stringuri:\n";
    cout << "Introduceti un numarul diferit de 0 pentru fiecare string pe care vreti sa il cititi, apoi stringul, si tastati 0 cand ati terminat:\n";
    counter=1;
    while (counter != 0) {
        cin >> counter;
        if (counter ) {
            in >> x;
            m.m_listaImporturi.push_back(x);
        } }
    return in;
}
ostream& operator<< (ostream& out, Rootkit& m){
    cout << static_cast<Malware&>(m);
    cout << "\nLista importurilor:";
    for (int i=0; i<m.m_listaImporturi.size(); i++)
        out << "importul " << i+1 << m.m_listaImporturi[i];
    cout << "\nLista stringurilor:";
    for (int i=0; i<m.m_listaStringuri.size(); i++)
        out << "importul " << i+1 << m.m_listaStringuri[i] ;
    cout << endl;
    return out;
}



class Keylogger: public Malware {
protected:
    vector<string> m_listaFunctii, m_listaTaste;
public:
    Keylogger();
    Keylogger(double rating, const string &data, const string &nume, const string &metodaInfectare,
              const vector<string> &registri, const vector<string> &listaFunctii, const vector<string> &listaTaste);

    virtual ~Keylogger(){}
    Keylogger(const Keylogger& m);
    virtual Keylogger& operator=(Keylogger m);
    friend istream& operator>> (istream& in, Keylogger& m);
    friend ostream& operator<< (ostream& out, Keylogger& m);
};
istream& operator>> (istream& in, Keylogger& m){
    cin >> static_cast<Malware&>(m);
    cout << "Introduceti lista de functii:\n";
    cout << "Introduceti un numarul diferit de 0 pentru fiecare functie pe care vreti sa il cititi, apoi functia, si tastati 0 cand ati terminat:\n";
    int counter=1; string x;
    while (counter != 0) {
        cin >> counter;
        if (counter ) {
            in >> x;
            m.m_listaFunctii.push_back(x);
        } }
    cout << "Introduceti lista de taste speciale:\n";
    cout << "Introduceti un numarul diferit de 0 pentru fiecare tasta pe care vreti sa il cititi, apoi tasta, si tastati 0 cand ati terminat:\n";
    counter=1;
    while (counter != 0) {
        cin >> counter;
        if (counter ) {
            in >> x;
            m.m_listaTaste.push_back(x);
        } }
    return in;
}
ostream& operator<< (ostream& out, Keylogger& m){
    cout << static_cast<Malware&>(m);
    cout << "\nLista functiilor:";
    for (int i=0; i<m.m_listaFunctii.size(); i++)
        out << "importul " << i+1 << m.m_listaFunctii[i];
    cout << "\nLista tastelor speciale:";
    for (int i=0; i<m.m_listaTaste.size(); i++)
        out << "importul " << i+1 << m.m_listaTaste[i] ;
    cout << endl;
    return out;
}
Keylogger::Keylogger(const Keylogger& m){
    for (int i=0; i<m.m_listaFunctii.size(); i++)
        m_listaFunctii.push_back(m.m_listaFunctii[i]);

    for (int i=0; i<m.m_listaTaste.size(); i++)
        m_listaTaste.push_back(m.m_listaTaste[i]);
}
Keylogger& Keylogger::operator=(Keylogger m){
    for (int i=0; i<m.m_listaFunctii.size(); i++)
        m_listaFunctii.push_back(m.m_listaFunctii[i]);

    for (int i=0; i<m.m_listaTaste.size(); i++)
        m_listaTaste.push_back(m.m_listaTaste[i]);
    return *this;
}
Keylogger::Keylogger() {
    m_listaTaste = m_listaFunctii = {};
}
Keylogger::Keylogger(double rating, const string &data, const string &nume, const string &metodaInfectare,
                     const vector<string> &registri, const vector<string> &listaFunctii,
                     const vector<string> &listaTaste) : Malware(rating, data, nume, metodaInfectare, registri),
                     m_listaFunctii(listaFunctii), m_listaTaste(listaTaste) {}





class KernelKeylogger: virtual public Rootkit, virtual public Keylogger {
    bool m_ascundeFisiere, m_ascundeRegistri;
public:
    KernelKeylogger();
    KernelKeylogger(double rating, const string &data, const string &nume, const string &metodaInfectare,
                    const vector<string> &registri, const vector<string> &listaImporturi,
                    const vector<string> &listaStringuri, double rating1, const string &data1, const string &nume1,
                    const string &metodaInfectare1, const vector<string> &registri1, const vector<string> &listaFunctii,
                    const vector<string> &listaTaste, bool ascundeFisiere, bool ascundeRegistri);

//    KernelKeylogger(const KernelKeylogger& m);
//    virtual KernelKeylogger& operator=(KernelKeylogger m);
    friend istream& operator>> (istream& in, KernelKeylogger& m);
    friend ostream& operator<< (ostream& out, KernelKeylogger& m);
};
istream& operator>> (istream& in, KernelKeylogger& m){
    cin >> static_cast<Rootkit&>(m);    // apelez citirea doar pentru rootkit, apoi citesc explicit aici datele specifice pentru keylogger
    cout << "Introduceti lista de functii:\n";
    cout << "Introduceti un numarul diferit de 0 pentru fiecare functie pe care vreti sa il cititi, apoi functia, si tastati 0 cand ati terminat:\n";
    int counter=1; string x;
    while (counter != 0) {
        cin >> counter;
        if (counter ) {
            in >> x;
            m.m_listaFunctii.push_back(x);
        } }
    cout << "Introduceti lista de taste speciale:\n";
    cout << "Introduceti un numarul diferit de 0 pentru fiecare tasta pe care vreti sa il cititi, apoi tasta, si tastati 0 cand ati terminat:\n";
    counter=1;
    while (counter != 0) {
        cin >> counter;
        if (counter ) {
            in >> x;
            m.m_listaTaste.push_back(x);
        } }
    // acum citesc datele specifice acestei clase
    cout << "Introduceti 1 daca au fost ascunse fisiere sau 0 in caz contrar:\n";
    in >> m.m_ascundeFisiere;
    cout << "Introduceti 1 daca au fost ascunse registri sau 0 in caz contrar:\n";
    in >> m.m_ascundeRegistri;
    return in;
}
ostream& operator<< (ostream& out, KernelKeylogger& m){
    cout << static_cast<Rootkit&>(m);   // la fel, afisez rootkit-ul si apoi explicit doar datele specifice din keylogger
    cout << "\nLista functiilor:";
    for (int i=0; i<m.m_listaFunctii.size(); i++)
        out << "importul " << i+1 << m.m_listaFunctii[i];
    cout << "\nLista tastelor speciale:";
    for (int i=0; i<m.m_listaTaste.size(); i++)
        out << "importul " << i+1 << m.m_listaTaste[i] ;
    cout << endl;
    // acum afisez datele specifice acestei clase
    if (m.m_ascundeFisiere)
        cout << "Au fost ascunse fisiere.\n";
    else cout << "Nu au fost ascunse fisiere.\n";
    if (m.m_ascundeRegistri)
        cout << "Au fost ascunsi registri.\n";
    else cout << "Nu au fost ascunsi registri.\n";
    return out;
}
//KernelKeylogger::KernelKeylogger(const KernelKeylogger& m){
//
//}
//KernelKeylogger& KernelKeylogger::operator=(KernelKeylogger m){
//
//}
KernelKeylogger::KernelKeylogger() {
    m_ascundeRegistri = m_ascundeFisiere = 0;
}
KernelKeylogger::KernelKeylogger(double rating, const string &data, const string &nume, const string &metodaInfectare,
                                 const vector<string> &registri, const vector<string> &listaImporturi,
                                 const vector<string> &listaStringuri, double rating1, const string &data1,
                                 const string &nume1, const string &metodaInfectare1, const vector<string> &registri1,
                                 const vector<string> &listaFunctii, const vector<string> &listaTaste,
                                 bool ascundeFisiere, bool ascundeRegistri) : Rootkit(rating, data, nume, metodaInfectare, registri, listaImporturi, listaStringuri),
                                                            Keylogger(rating1, data1, nume1, metodaInfectare1, registri1, listaFunctii, listaTaste),
                                                            m_ascundeFisiere(ascundeFisiere), m_ascundeRegistri(ascundeRegistri) {}


class Ransomware: public Malware {
    int m_ratingCriptare;
    double m_ratingObfuscare;
public:
    Ransomware();
    Ransomware(double rating, const string &data, const string &nume, const string &metodaInfectare,
               const vector<string> &registri, int ratingCriptare, double ratingObfuscare);

    friend istream& operator>> (istream& in, Ransomware& m);
    friend ostream& operator<< (ostream& out, Ransomware& m);
};
istream& operator>> (istream& in, Ransomware& m){
    cin >> static_cast<Malware&>(m);
    cout<< "Introduceti ratingul de criptare:\n";
    in >> m.m_ratingCriptare;
    cout<< "Introduceti ratingul de obfuscare:\n";
    in >> m.m_ratingObfuscare;
    return in;
}
ostream& operator<< (ostream& out, Ransomware& m){
    cout << static_cast<Malware&>(m);
    out << "\nRatingul de criptare:" << m.m_ratingCriptare;
    out << "\nRatingul de obfuscare:" << m.m_ratingObfuscare;
    cout << endl;
    return out;
}
Ransomware::Ransomware() {
    m_ratingCriptare = 0;
    m_ratingObfuscare = 0;
}
Ransomware::Ransomware(double rating, const string &data, const string &nume, const string &metodaInfectare,
            const vector<string> &registri, int ratingCriptare, double ratingObfuscare) : Malware(rating,data, nume,metodaInfectare,registri),
            m_ratingCriptare(ratingCriptare), m_ratingObfuscare(ratingObfuscare) {}



class Computer {
    static int m_id;
    vector<Malware> m_listaMalware;
    double m_ratingFinal;
public:
    Computer();
    Computer(const vector<Malware> &listaMalware, double ratingFinal);
    vector<Malware> getMalware();   // getter de lista de malware-e pentru this computer => folosita in meniu
};
int Computer::m_id=0;
Computer::Computer() {
    m_id++;
    m_listaMalware = {};
    m_ratingFinal = 0;
}
Computer::Computer(const vector<Malware> &listaMalware, double ratingFinal) :
    m_listaMalware(listaMalware), m_ratingFinal(ratingFinal) {
    m_id++;
}
vector<Malware> Computer::getMalware() {
    return m_listaMalware;
}



class Meniu {
public:
    Meniu();
    Meniu(const vector<Computer> &computere);
    void afisInf();
    void adaugaComputer(Computer c);
private:
    vector<Computer> m_computere;

};
Meniu::Meniu() {
    m_computere = {};
}
Meniu::Meniu(const vector<Computer> &computere) : m_computere(computere) {}
void Meniu::afisInf() {
    // pentru fiecare computer din firma:
    for (int i=0; i<m_computere.size(); i++)
    {
        // m va retine lista malware-lor acestui computer
        vector<Malware> m = m_computere[i].getMalware();
        // pentru fiecare malware din lista acestui computer
        for (int j=0; j<m.size(); i++) {
            // verific daca e fiecare tip de malware in parte
            auto isRootkit = dynamic_cast<Rootkit&>(m[j]);
            auto isKeylogger = dynamic_cast<Keylogger&>(m[j]);
            auto isKernelKeylogger = dynamic_cast<KernelKeylogger&>(m[j]);
            auto isRansomeware = dynamic_cast<Ransomware&>(m[j]);

            // citesc si afisez malware-ul specific

            if (&isRootkit)  {
                //cin >> m[j];
                cout << m[j];
            }
            else if (&isKeylogger){
                //cin >> m[j];
                cout << m[j];
            }
            else if (&isKernelKeylogger){
                //cin >> m[j];
                cout << m[j];
            }
            else if (&isRansomeware){
                //cin >> m[j];
                cout << m[j];
            }
        }
    }
}



int main()
{
    Meniu meniu;
    Computer c1;
    // meniu.adaugaComputer(c1);
    int x;
    cout << "Tastati 1 pentru cerinta 1.\n";
    cin >> x;
    if (x==1)   meniu.afisInf();


    Malware m1(2,"80", "jk", "jk", {"fd","ds"});
    // cin >> m1;
    // cout << m1;
    Rootkit roo1;
    // cin >> roo1;
    // cout << roo1;
    Ransomware r1;
    // cin >> r1;
    // cout << r1;
    Keylogger k1;
    // cin >> k1;
    // cout << k1;
    KernelKeylogger kl1;
    // cin >> kl1;
    // cout << kl1;

    return 0;
}
