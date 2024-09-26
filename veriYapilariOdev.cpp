#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

class Urun
{
public:
    Urun() : barkod(-1), isim_(""), kategori(""), next(nullptr) {}
    Urun(string urunIsim, string kategori)
        : barkod(-1), isim_(urunIsim), kategori(kategori), next(nullptr) {}
    string getIsim() const { return isim_; }
    string getKategori() const { return kategori; }
    int getBarkod() const { return barkod; }
    void setBarkod(int sn) { barkod = sn; }
    Urun *getNext() const { return next; }
    void setNext(Urun *n) { next = n; }
    void setIsim(const string &yeniIsim) { isim_ = yeniIsim; }
    void setKategori(const string &yeniKategori) { kategori = yeniKategori; }

private:
    int barkod;
    string isim_;   
    string kategori;
    Urun *next;
};

class UrunListesi
{
public:
    UrunListesi()
        : head(nullptr)
    {
        varsayilanUrunleriEkle();
    }

    void varsayilanUrunleriEkle()
    {
        urunEkle(Urun("Ekmek", "Gida"));
        urunEkle(Urun("Sampuan", "Temizlik"));
        urunEkle(Urun("Su", "Gida"));
        urunEkle(Urun("Usb", "Ev Aletleri"));
        urunEkle(Urun("Pirinc", "Gida"));
        urunEkle(Urun("Sabun", "Temizlik"));
        urunEkle(Urun("Camasir Suyu", "Temizlik"));
        urunEkle(Urun("Pil", "Ev Aletleri"));
        urunEkle(Urun("Domates", "Gida"));
        urunEkle(Urun("Ampul", "Ev Aletleri"));
    }

    void urunleriSirala()
    {
        if (!head || !head->getNext())
            return;

        Urun *current = head;
        Urun *index = nullptr;
        string tempIsim;
        string tempKategori;
        int tempBarkod;

        while (current)
        {
            index = current->getNext();

            while (index)
            {
                if (current->getKategori() > index->getKategori())
                {
                    tempIsim = current->getIsim();
                    tempKategori = current->getKategori();
                    tempBarkod = current->getBarkod();

                    current->setIsim(index->getIsim());
                    current->setKategori(index->getKategori());
                    current->setBarkod(index->getBarkod());

                    index->setIsim(tempIsim);
                    index->setKategori(tempKategori);
                    index->setBarkod(tempBarkod);
                }
                index = index->getNext();
            }
            current = current->getNext();
        }
    }

    void urunleriYazdir()
    {
        cout << "*********************" << endl;
        urunleriSirala();
        int barkod = 1;
        Urun *current = head;
        while (current)
        {
            current->setBarkod(barkod++);
            cout << "Barkod: " << current->getBarkod() << ", Isim: " << current->getIsim() << endl;
            current = current->getNext();
        }
        cout << "*********************" << endl;
        if (!getHead())
        {
            cout << "Urun listesi bos." << endl;
        }
    }

    void urunEkle(const Urun &urun)
    {
        Urun *newNode = new Urun(urun.getIsim(), urun.getKategori());
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Urun *current = head;
            while (current->getNext())
            {
                current = current->getNext();
            }
            current->setNext(newNode);
        }
    }

    void urunSil(int barkod)
    {
        if (!head)
            return;

        Urun *temp = head;
        Urun *prev = nullptr;

        if (temp->getBarkod() == barkod)
        {
            head = temp->getNext();
            delete temp;
            return;
        }

        while (temp && temp->getBarkod() != barkod)
        {
            prev = temp;
            temp = temp->getNext();
        }

        if (!temp)
            return;

        prev->setNext(temp->getNext());
        delete temp;
    }

    ~UrunListesi()
    {
        while (head)
        {
            Urun *temp = head;
            head = head->getNext();
            delete temp;
        }
    }

    Urun *getHead() const { return head; }

private:
    Urun *head;
};

class Sepet
{
public:
    stack<Urun> sepet;

    void sepeteUrunEkle(Urun urun)
    {
        sepet.push(urun);
    }

    void sepettenUrunCikar(int barkod)
    {
        if (sepet.empty())
        {
            cout << "Sepet bos." << endl;
            return;
        }

        stack<Urun> temp;
        Urun urun;
        bool bulundu = false;

        while (!sepet.empty())
        {
            urun = sepet.top();
            sepet.pop();
            if (urun.getBarkod() == barkod)
            {
                bulundu = true;
                break;
            }
            temp.push(urun);
        };

        while (!temp.empty())
        {
            sepet.push(temp.top());
            temp.pop();
        }

        if (bulundu)
        {
            cout << "Urun cikarildi - Barkod: " << urun.getBarkod() << ", Isim: " << urun.getIsim() << endl;
        }
        else
        {
            cout << "Barkod numarasi " << barkod << " olan urun bulunamadi." << endl;
        }
    }

    void sepetiGoster()
    {
        if (sepet.empty())
        {
            cout << "Sepet bos." << endl;
            return;
        }

        cout << "Sepetteki Urunler:" << endl;
        stack<Urun> temp = sepet;
        while (!temp.empty())
        {
            Urun urun = temp.top();
            cout << "Barkod: " << urun.getBarkod() << ", Isim: " << urun.getIsim() << endl;
            temp.pop();
        }
    }
};

class KasaKuyrugu
{
public:
    queue<string> kuyruk;

    void musteriEkle(const string &musteriAdi)
    {
        kuyruk.push(musteriAdi);
        cout << musteriAdi << " kuyruga eklendi." << endl;
    }

    void musteriCikar()
    {
        if (kuyruk.empty())
        {
            cout << "Kuyruk bos." << endl;
            return;
        }

        cout << kuyruk.front() << " kuyruktan cikarildi." << endl;
        kuyruk.pop();
    }

    void kuyruktakiMusterileriGoster()
    {
        if (kuyruk.empty())
        {
            cout << "Kuyruk bos." << endl;
            return;
        }

        cout << "Kuyruktaki Musteriler:" << endl;
        queue<string> temp = kuyruk;
        while (!temp.empty())
        {
            cout << temp.front() << endl;
            temp.pop();
        }
    }
    void varsayilanKuyrukEkle(KasaKuyrugu &kasaKuyrugu)
    {
        kasaKuyrugu.musteriEkle("Ahmet");
        kasaKuyrugu.musteriEkle("Mehmet");
        kasaKuyrugu.musteriEkle("Ayse");
        kasaKuyrugu.musteriEkle("Fatma");
    }
};

int main()
{
    UrunListesi urunListesi;
    KasaKuyrugu kasaKuyrugu;
    kasaKuyrugu.varsayilanKuyrukEkle(kasaKuyrugu);

    while (true)
    {
        int kullaniciSecim;
        cout << "1. Calisan Islemleri\n2. Musteri Islemleri\n3. Kasa Islemleri\n4. Cikis\nSeciminizi girin: ";
        cin >> kullaniciSecim;

        if (kullaniciSecim == 1)
        {
            cout << "Calisan Islemleri\n";
            while (true)
            {
                int secim;
                cout << "1. Urun Ekle\n2. Urun Sil\n3. Urunleri Yazdir\n4. Kasa Kuyrugunu Goruntule\n5. Kuyruktan Musteri Cikar\n6. Geri \nSeciminizi girin: ";
                cin >> secim;

                if (secim == 1)
                {
                    string isim, kategori;
                    cout << "Isim Girin: ";
                    cin.ignore();
                    getline(cin, isim);
                    cout << "Kategori Girin: ";
                    getline(cin, kategori);
                    urunListesi.urunEkle(Urun(isim, kategori));
                }
                else if (secim == 2)
                {
                    int barkod;
                    urunListesi.urunleriYazdir();
                    cout << "Barkod Girin: ";
                    cin >> barkod;
                    urunListesi.urunSil(barkod);
                }
                else if (secim == 3)
                {
                    urunListesi.urunleriYazdir();
                }
                else if (secim == 4)
                {
                    kasaKuyrugu.kuyruktakiMusterileriGoster();
                }
                else if (secim == 5){
                    kasaKuyrugu.musteriCikar();
                }
                else if (secim == 6)
                {
                    break;
                }
            }
        }
        else if (kullaniciSecim == 2)
        {
            cout << "Musteri Islemleri\n";
            Sepet sepet;
            while (true)
            {
                int secim;
                cout << "1. Sepete Urun Ekle\n2. Sepetten Urun Cikar\n3. Sepeti Goster\n4. Kasa Kuyrugunu Goruntule\n5. Geri \nSeciminizi girin: ";
                cin >> secim;
                if (secim == 1)
                {

                    urunListesi.urunleriYazdir();
                    int barkod;
                    cout << "Sepete eklemek istediginiz urunun barkodunu girin: ";
                    cin >> barkod;
                    Urun *urun = nullptr;
                    Urun *current = urunListesi.getHead();
                    while (current)
                    {
                        if (current->getBarkod() == barkod)
                        {
                            urun = current;
                            break;
                        }
                        current = current->getNext();
                    }

                    if (urun)
                    {
                        sepet.sepeteUrunEkle(*urun);
                        cout << "Urun sepete eklendi." << endl;
                    }
                    else
                    {
                        cout << "Barkod numarasi " << barkod << " olan urun bulunamadi." << endl;
                    }
                }

                else if (secim == 2)
                {
                    sepet.sepetiGoster();
                    if (!sepet.sepet.empty())
                    {
                        int barkod;
                        cout << "Sepetten cikarmak istediginiz urunun barkodunu girin: ";
                        cin >> barkod;
                        sepet.sepettenUrunCikar(barkod);
                    }
                }
                else if (secim == 3)
                {
                    sepet.sepetiGoster();
                }
                else if (secim == 4)
                {
                    kasaKuyrugu.kuyruktakiMusterileriGoster();
                }
                else if (secim == 5)
                {
                    break;
                }
                else
                {
                    cout << "Gecersiz secim. Tekrar deneyin." << endl;
                }
            }
        }
        else if (kullaniciSecim == 3)
        {
            while (true)
            {
                int kasaSecim;
                cout << "1. Kuyruga Musteri Ekle\n2. Kuyruktaki Musterileri Goster\n3. Geri \nSeciminizi girin: ";
                cin >> kasaSecim;

                if (kasaSecim == 1)
                {
                    string musteriAdi;
                    cout << "Musteri Adi Girin: ";
                    cin.ignore();
                    getline(cin, musteriAdi);
                    kasaKuyrugu.musteriEkle(musteriAdi);
                }
                else if (kasaSecim == 2)
                {
                    kasaKuyrugu.kuyruktakiMusterileriGoster();
                }
                else if (kasaSecim == 3)
                {
                    break;
                }
                else
                {
                    cout << "Gecersiz secim. Tekrar deneyin." << endl;
                }
            }
        }
        else if (kullaniciSecim == 4)
        {
            break;
        }
        else
        {
            cout << "Gecersiz secim. Tekrar deneyin." << endl;
        }
    }
}
