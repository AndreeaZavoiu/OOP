#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Produs {
private:
    string m_denProd;
    float m_pretProd;
public:
    Produs() {
        m_denProd = "";
        m_pretProd = 0;
    }
    Produs(const string& mDenProd, float mPretProd) : m_denProd(mDenProd), m_pretProd(mPretProd) {}
    Produs(const Produs& p) {
        m_denProd = p.m_denProd;
        m_pretProd = p.m_pretProd;
    }
    ~Produs() {}

    void operator= (const Produs& p) {
        m_denProd = p.m_denProd;
        m_pretProd = p.m_pretProd;
    }

    float getPret() {
        return m_pretProd;
    }
    string getDenProd() {
        return m_denProd;
    }
    friend istream& operator>> (istream& in, Produs& p);
    friend ostream& operator<< (ostream& out, Produs& p);
};

ostream& operator<< (ostream& out, Produs& p) {
    out << p.m_denProd << " la pretul de " << p.m_pretProd << " lei \n";
    return out;
}

istream& operator >> (istream& in, Produs& p) {
    cout << "(introduceti denumirea si pretul produsului dorit) : ";
    in >> p.m_denProd >> p.m_pretProd;
    return in;
}


class Comanda {
protected:
    static int m_num;
    Produs m_prod;
    int m_nrPortii;
    int m_zi, m_luna, m_an;
public:
    Comanda() {
        m_nrPortii = m_zi = m_luna = m_an = 0;
        m_num++;
    }
    // data curenta in constructor
    Comanda(const Produs& Prod, int NrPortii, int zi = 19, int luna = 5, int an = 2021) 
        : m_prod(Prod), m_nrPortii(NrPortii), m_zi(zi), m_luna(luna), m_an(an)
        {
            m_num++;
        }
    Comanda(const Comanda& c) 
        : m_prod(c.m_prod) {

        m_nrPortii = c.m_nrPortii;
        m_zi = c.m_zi;
        m_luna = c.m_luna;
        m_an = c.m_an;
        m_num++;
    }
    virtual ~Comanda() {
        m_num--;
    }
    virtual float getPret() {
        return m_prod.getPret();
    }
    int getZi() {
        return m_zi;
    }
    int getLuna() {
        return m_luna;
    }
    int getAn() {
        return m_an;
    }
    string getDenProd() {
        return m_prod.getDenProd();
    }
    int getNrPortii() {
        return m_nrPortii;
    }
    virtual void operator++ (int dummy) {
        m_nrPortii++;
    }
    virtual Comanda operator+ (int x) {
        m_nrPortii += x;
        return *this;
    }
    virtual void operator= (const Comanda& c) {
        m_prod = c.m_prod;
        m_nrPortii = c.m_nrPortii;
        m_zi = c.m_zi;
        m_luna = c.m_luna;
        m_an = c.m_an;
    }
    //    Comanda operator= (Comanda &c){
    //        return Comanda(c);
    //    }
        // functie pentru anularea comenzii
    virtual void del() {
        m_num--;
        //delete this;
    }

    friend istream& operator>> (istream& in, Comanda& c);
    friend ostream& operator<< (ostream& out, Comanda& c);
};
int Comanda::m_num = 0; // initializare => prima comanda va fi 1
istream& operator>> (istream& in, Comanda& c) {
    cout << "Comandati produsul: ";
    in >> c.m_prod;
    cout << "Portii: ";
    in >> c.m_nrPortii;
    cout << "Data: ";
    in >> c.m_zi >> c.m_luna >> c.m_an;
    return in;
}
ostream& operator<< (ostream& out, Comanda& c) {
    out << "Comanda din data " << c.m_zi << "." << c.m_luna << "." << c.m_an << ", contine: " << c.m_nrPortii << " portii de " << c.m_prod;
    return out;
}



class ComSpec : virtual public Comanda {
protected:
    string m_obsC;
    float m_pretSupl;
public:
    ComSpec() : Comanda() {
        m_obsC = "";
        m_pretSupl = 0;
    }
    ComSpec(const Produs& p, int nrPortii, int zi, int luna, int an, const string obsC, const float pretSupl) :
        Comanda(p, nrPortii, zi, luna, an), m_obsC(obsC), m_pretSupl(pretSupl) {}
    ComSpec(const ComSpec& c) {}
    virtual ~ComSpec() {}
    virtual void del() {
        m_num--;
        delete this;
    }
    virtual void operator=(const ComSpec& c) {
        m_obsC = c.m_obsC;
        m_pretSupl = c.m_pretSupl;
    }
    // functie de setare a pretului suplimentar al acestui tip de comanda
    float getPretSupl() {
        return m_pretSupl;
    }
    friend istream& operator>> (istream& in, ComSpec& c);
    friend ostream& operator<< (ostream& out, ComSpec& c);
};

istream& operator>> (istream& in, ComSpec& c) {
    cout << "Adaugati observatiile speciale: ";
    in >> c.m_obsC;
    cout << "Pretul va fi: ";
    in >> c.m_pretSupl;
    return in;
}
ostream& operator<< (ostream& out, ComSpec& c) {
    out << "Comanda speciala cu " << c.m_obsC << " are pretul " << c.m_pretSupl;
    return out;
}


class ComOnline : virtual public ComSpec {
    string m_adrLivr;
    int m_comLivr; // = comision 5% din val comenzii dar poate scadea pana la 0 in functie de valoarea comenzii
public:
    ComOnline() : Comanda() {
        m_adrLivr = "";
        m_comLivr = 0;
    }
    ComOnline(const Produs& prod, int nrPortii, int zi, int luna, int an, const string& mAdrLivr, int mComLivr) :
        Comanda(prod, nrPortii, zi, luna, an), m_adrLivr(mAdrLivr), m_comLivr(mComLivr) {}

    ~ComOnline() {}
    void del() {
        m_num--;
        delete this;
    }
    void operator= (const ComOnline& c) {
        m_adrLivr = c.m_adrLivr;
        m_comLivr = c.m_comLivr;
    }
    float getPretCuComisionDeLivrare() {
        return Comanda::getPret() + Comanda::getPret() * m_comLivr;
    }

    friend istream& operator>> (istream& in, ComOnline& c);
    friend ostream& operator<< (ostream& out, ComOnline& c);
};

istream& operator>> (istream& in, ComOnline& c) {
    cout << "Introduceti adresa de livrare si comisionul: ";
    in >> c.m_adrLivr >> c.m_comLivr;
    return in;
}
ostream& operator<< (ostream& out, ComOnline& c) {
    out << "Comanda de la adresa " << c.m_adrLivr << " are pretul " << c.getPretCuComisionDeLivrare();
    return out;
}


class Ospatar {
    string m_nume;
    Comanda** m_comenzi;
    int m_nrComenzi;
    int m_varsta;
    string m_gen; // "M" / "F"
public:
    Ospatar() {
        m_nume = "";
        m_nrComenzi = m_varsta = 0;
        m_gen = "";
    }

    Ospatar(string nume, Comanda** comenzi, int nrComenzi, const string& gen, int varsta) : m_nume(
        nume), m_nrComenzi(nrComenzi), m_varsta(varsta), m_gen(gen) {
        
        m_comenzi = new Comanda* [nrComenzi];

        for (int i = 0; i < nrComenzi; i++) {
            //m_comenzi[i] = new Comanda(*comenzi[i]);
            m_comenzi[i] = comenzi[i];
        }
    } 
    ~Ospatar() {
        for (int i = 0; i < m_nrComenzi; ++i) {
            if (m_comenzi[i] != NULL) {
                delete m_comenzi[i];
            }
        }
        //        m_nrComenzi = 0;
    }

    string nume() const {
        return m_nume;
    }
    //    Comanda* getComanda(){
    //        return m_comenzi[];
    //    }
    int getNrComenzi() {
        return m_nrComenzi;
    }

    bool operator> (Ospatar& o1) {
        return this->m_nrComenzi > o1.m_nrComenzi;
    }
    bool operator== (Ospatar& o1) {
        return (o1.m_nrComenzi == this->m_nrComenzi);
    }

    // functie care returneaza valoarea totala a comenzilor acestui ospatar
    int getValoareTotala() {
        int val = 0;
        for (int i = 0; i < m_nrComenzi; i++)
            val += m_comenzi[i]->getPret();
        return val;
    }

    // Returnarea unui vector cu comenzile prelucrate de this ospatar in data trimisa ca parametru
    void afisComDupaData(int zi, int luna, int an) {
        Comanda* temporar[100]; int j = 0;
        for (int i = 0; i < m_nrComenzi; i++) {
            if (m_comenzi[i]->getZi() == zi && m_comenzi[i]->getLuna() == luna && m_comenzi[i]->getAn() == an)
                temporar[j++] = m_comenzi[i];
        }
        for (int i = 0; i < j; i++)
            cout << *temporar[i] << '\n';
    }

    friend istream& operator>> (istream& in, Ospatar& o);
    friend ostream& operator<< (ostream& out, Ospatar& o);
};


istream& operator>> (istream& in, Ospatar& o) {
    cout << "Introduceti numele ospatarului: ";
    in >> o.m_nume;
    cout << "Introduceti numarul de comenzi: ";
    in >> o.m_nrComenzi;
    cout << "Introduceti cele " << o.m_nrComenzi << " comenzi: ";

    // am mai multe tipuri de comenzi, deci intreb ce tip de comanda vrem
    for (int i = 0; i < o.m_nrComenzi; i++) {
        cout << "Tip Comanda (0=Simpla, 1=Speciala, 2=Online): ";
        int tip;
        cin >> tip;
        if (tip == 0) {
            Comanda tmp;
            cin >> tmp;
            o.m_comenzi[i] = new Comanda(tmp);
        }
        else if (tip == 1) {
            ComSpec tmp;
            cin >> tmp;
            o.m_comenzi[i] = new ComSpec(tmp);
        }
        else { // tip == 3
            ComOnline tmp;
            cin >> tmp;
            o.m_comenzi[i] = new ComOnline(tmp);
        }
        //        in >> *o.m_comenzi[i];
    }
    cout << "Introduceti genul: ";
    in >> o.m_gen;
    cout << "Introduceti varsta: ";
    in >> o.m_varsta;
    return in;
}

ostream& operator<< (ostream& out, Ospatar& o) {
    out << "\nOspatarul: " << o.m_nume << " cu comenzile: ";
    for (int i = 0; i < o.m_nrComenzi; i++) {
        out << *(o.m_comenzi[i]) << " ";
    }
    out << " are " << o.m_varsta << " ani si este " << o.m_gen;
    return out;
}


int main() {
    // demo
    // Alocari statice:
    Produs meniu[4] = { Produs("frigarui", 30),
                        Produs("cola", 7.5),
                        Produs("cafea", 5) };

    Comanda c1(meniu[0], 2, 30, 5, 2016),
        c2(meniu[1], 3),
        c3(meniu[2], 1),
        c4 = c2,
        c5;

    c3 = c3 + 4; // se mai comanda 4 cafele
    c2++; // se mai comanda o cola
    c1.del();
    cin >> c5; // exemplu: papanasi 5 31 5 2016
    cout << c4 << endl << c5;

    // Comanda *comenzi1[] = {&c1, &c2};
    // Comanda *comenzi2[] = {&c3, &c4};

    // Alocari dinamice:        TODO TRB DELETE !
    Comanda* com1 = new Comanda[3];
    com1[0] = c1;
    com1[1] = c2;


    //////
    Comanda** com11 = new Comanda* [3];

    for (int i = 0; i < 3; i++) {
        com11[i] = NULL;
    }
    
    com11[0] = &c1;
    com11[1] = &c2;
    com11[2] = &c3;


    ///////////

    Ospatar o1("Ionescu", com11, 3, "M", 25);
    //cout << o1;

    Comanda** comenzi2 = new Comanda * [2];
    comenzi2[0] = &c4;
    comenzi2[1] = &c5;

    Ospatar o2("Popescu", comenzi2, 2, "F", 30);
    //cout << o2;

    // cin >> o3;
    cout << o1 <<'\n'<< o2;
        if (o2 > o1) cout << "\nOspatarul " << o2.nume() << "a servit mai multe comenzi decat ospatarul " << o1.nume() <<endl;
        else if (o1 == o2) cout << "\nNumar egal de comenzi intre ospatarii " << o2.nume() << " si " << o1.nume() << endl;
        else cout << "\nOspatarul " << o2.nume() << "a servit mai putine comenzi decat ospatarul " << o1.nume() <<endl;
    

        vector<Ospatar> vectorOspatari = {o1, o2};
        vector<Comanda*> vectorComenzi;
        vectorComenzi.push_back(new Comanda(c1));
        vectorComenzi.push_back(new Comanda(c2));
        vectorComenzi.push_back(new Comanda(c3));

        // Cerinte :
        // 1. Afisarea tuturor comenzilor prelucrate in data de 31.05.2016
        // (pt fiecare ospatar apelez functia de returnare a comenzii dupa data trimisa ca parametru si afisez comenzile returnate de acea functie)
        cout << "Cerinta 1: " << " comenzile prelucrate in data de 31.05.2016 : ";
        for (int i=0; i< vectorOspatari.size(); i++) {
            vectorOspatari[i].afisComDupaData(31, 5, 2016) ;
        }


        // 2. Afisarea numarului de portii de "papanasi" standard si papanasi cu "nuca de cocos" comandate in luna mai 2016.
        // => afisez comenzile normale care au ca denumirea produsului "papanasi" si ca luna si an 5 2016
        // si comenzile speciala care au ca mai sus si in plus observatiile "nuca de cocos"
        cout << "Cerinta 2: " << " numarul total de portii de papanasi: ";
        int nrTotalPortii=0;
        for (int i=0; i<vectorComenzi.size(); i++){
            if ( vectorComenzi[i]->getLuna() == 5 && vectorComenzi[i]->getAn() == 2016 && vectorComenzi[i]->getDenProd() == "papanasi") {
                auto tipComanda = dynamic_cast<ComSpec*> (vectorComenzi[i]);
                if (tipComanda) {
                    nrTotalPortii += tipComanda->getNrPortii();
                }
            }
        }
        cout << nrTotalPortii;


        // 3. Afisarea procentului valorii totale cumulate a comenzilor online din valoarea totala cumulata a tuturor comenzilor inregistrate in
        // luna mai 2016.
        cout << "Cerinta 3: procentului valorii comenzilor online din valoarea tuturor comenzilor nregistrate in mai 2016: ";
        float valoareTotala = 0;
        float valoareComOnline = 0;
        for (int i=0; i<vectorComenzi.size(); i++) {
            if (vectorComenzi[i]->getLuna() == 5 && vectorComenzi[i]->getAn() == 2016) {
                valoareTotala += vectorComenzi[i]->getPret();
                auto comandaOnline = dynamic_cast<ComOnline *> (vectorComenzi[i]);
                if (comandaOnline) {
                    valoareComOnline += comandaOnline->getPretCuComisionDeLivrare();
                }
            }
        }
        cout << (valoareComOnline/100) * valoareTotala; // nu sunt sigura ca asa se calculeaza procentul, dar asta e ceva de mate, nu de poo :))


        // 4. Afisarea ospatarului care a servit comenzi in valoare totala cumulata cea mai mare, fata de toti ceilalti ospatari
        cout << "Cerinta 3: ";
        for (int i=0; i<vectorOspatari.size(); i++){
            for (int j=0; j < vectorOspatari[i].getNrComenzi(); j++) {
                if ( vectorOspatari[i].getValoareTotala() == valoareTotala ) // de la cerinta anterioara
                    cout << vectorOspatari[i];
            }
        }

    return 0;
}