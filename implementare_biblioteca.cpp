/*
 8.	Bibilioteca: O biblioteca ofera suplimentar clientilor sai un serviciu de stocare si regasire a informatiilor.
 Astfel, fiecare client poate solicita ca bibilioteca sa memoreze informatii pe care el le-a furnizat si pe care le-a numit intr-un anumit fel.
 Informatiile de memorat pot fi de tip text (siruri de caractere), numeric (numere naturale), matematic (numere complexe) si
 de tip adresa (tara, judet, oras, strada, numar). De asemenea, informatiile pot avea un nume (e.g. “Adresa Mariei”, “Numarul meu preferat”).
 Odata introduse in bibilioteca, informatiile capata un ID. Biblioteca ofera urmatoarele servicii: Adaugare informatii,
 Stergere informatii dupa nume/ID, Regasire informatii (dupa Nume sau ID) si Cautare Informatii (dupa valoare – e.g. 27).
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class I_IO
{
public:
    virtual void citire(istream&) = 0;
    virtual void afisare(ostream&) = 0;

    friend istream& operator >>(istream& in, I_IO& ob)
    {
        ob.citire(in);
        return in;
    }
    friend ostream& operator <<(ostream& out, I_IO& ob)
    {
        ob.afisare(out);
        return out;
    }
};


class Informatie: public I_IO {
protected:
    string m_nume;
    static int m_id;
public:
    Informatie();
    Informatie(const string &nume);
    virtual void citire(istream& in);
    virtual string getNume();
    virtual Informatie& addInf(Informatie* i){
        return *this;
    }
};

int Informatie::m_id=0;
string Informatie::getNume() {
    return m_nume;
}
Informatie::Informatie() {
    m_nume = "";
}
Informatie::Informatie(const string &nume) : m_nume(nume) {}
void Informatie::citire(istream& in)
{
    cout << "Denumire: "; in >> m_nume;
}


class Text: virtual public Informatie {
    vector<string> m_inf;
public:
    Text();
    Text(const vector<string> &inf);
    void citire(istream& in);
    Text& addInf(Text* text);
};
Text& Text::addInf(Text* text) {
    for (int i=0; i<text->m_inf.size(); i++)
        m_inf.push_back(text->m_inf[i]);
    return *this;
}
Text::Text() {}
Text::Text(const vector<string> &inf) : Informatie(), m_inf(inf) {}
void Text::citire(istream& in)
{
    cout << "Text: "; // in >> m_inf;
}


class Numeric: virtual public Informatie {
    int m_inf;
public:
    Numeric();
    Numeric& addInf(Numeric* num);
    Numeric(int inf);
};
Numeric& Numeric::addInf(Numeric* num){
    m_inf += num->m_inf;
    return *this;
}
Numeric::Numeric() {  m_inf = 0;  }
Numeric::Numeric(int inf) : Informatie(), m_inf(inf) {}



class Matematic: virtual public Informatie {
    double m_real, m_imaginar;
public:
    Matematic();
    Matematic(double real, double imaginar);
    Matematic& addInf(Matematic* num);
};
Matematic& Matematic::addInf(Matematic* num){
    m_real += num->m_real;
    m_imaginar += num->m_imaginar;
    return *this;
}
Matematic::Matematic() {}
Matematic::Matematic(double real, double imaginar) : m_real(real), m_imaginar(imaginar) {}



class Adresa: virtual public Informatie {
public:
    Adresa() {}
    Adresa(const string &tara, const string &judet, const string &oras, const string &strada, int numar) : m_tara(tara),
                    m_judet(judet), m_oras(oras), m_strada(strada), m_numar(numar) {}

private:
    string m_tara, m_judet, m_oras, m_strada;
    int m_numar;
};



class Biblioteca {
    vector<Informatie*> info;
public:
    Biblioteca();
    Biblioteca(const vector<Informatie *> &info);

    Informatie& citireInf(Informatie &informatie);
    Informatie& adaugareInf(Informatie* informatie);
    void stergereInf();
    bool regasireInf();
    Informatie& cautareInf(int val);

};
Informatie& Biblioteca::adaugareInf( Informatie* informatie) {
    for (auto i=0; i<info.size(); i++){
        if (info[i]->getNume() == informatie->getNume()) {
            auto isText = dynamic_cast<Text *>(info[i]);
            auto isNumeric = dynamic_cast<Numeric *>(info[i]);
            auto isMatematic = dynamic_cast<Matematic *>(info[i]);
            auto isAdresa = dynamic_cast<Adresa *>(info[i]);

            try {
                if (isText) {
                    info[i]->addInf(informatie);
                    return *informatie;
                }
                else if (isNumeric || isMatematic) {
                    info[i]->addInf(informatie);
                    return *informatie;
                }
                else if (isAdresa) throw 505;
            }
            catch (...) { cout << "Eroare!"; }
        }

    }
}
Biblioteca::Biblioteca() {}
Biblioteca::Biblioteca(const vector<Informatie *> &info) : info(info) {}
Informatie& Biblioteca::citireInf(Informatie &informatie){
    informatie.citire(istream&);
}

int main() {
    Biblioteca b;


    return 0;
}
