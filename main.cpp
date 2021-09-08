/**
* Example of `builder' design pattern.
* The original of the study= https://refactoring.guru/design-patterns/builder/cpp/example
* This is a simplified and comment lines translated version of original.
*/

#include <iostream>
#include <vector>

class Product1 {
public:
    std::vector<std::string> parts_;
    void ListParts()const {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); i++) {
            if (parts_[i] == parts_.back()) {
                std::cout << parts_[i];
            }
            else {
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};


/*
* Builder s�n�f�nda par�a �retimi i�in kullan�lacak metodlar belirtildi.
*/
class Builder {
public:
    virtual ~Builder() {}
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};
/*
 * ConcreteBuilder1 s�n�f� yap�m i�lemi i�in gerekli uygulamalar� sa�lar.
 * Farkl� �ekillerde �al��an birden fazla builder s�n�f� bulunabilir.
 */
class ConcreteBuilder1 : public Builder {
private:

    Product1* product;

public:

    ConcreteBuilder1() {
        this->Reset();
    }

    ~ConcreteBuilder1() {
        delete product;
    }

    void Reset() {
        this->product = new Product1();
    }


    void ProducePartA()const override {
        this->product->parts_.push_back("PartA1");
    }

    void ProducePartB()const override {
        this->product->parts_.push_back("PartB1");
    }

    void ProducePartC()const override {
        this->product->parts_.push_back("PartC1");
    }

    /**
     *ConcreteBuilder'lar kendi metodlar�n� sa�layacaklar.
     *Bu y�zden farkl� aray�zlere sahip,
     *farkl� builderlardan �retilmi� farkl� �r�nler elde edilecek.
     */

    Product1* GetProduct() {
        Product1* result = this->product;
        this->Reset();
        return result;
    }
};

/**
 * ClientCode bir builder nesnesi yarat�yor.
 * Sonras�nda build s�reci ba�l�yor(yap�m s�reci)
 * Daha sonra d�n�� Builder nesnesinden al�n�yor.
 */

 //Bu k�s�m �zerinde de�i�iklik yap�ld�//
void ClientCode()
{
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    std::cout << "Standard basic product:\n";
    builder->ProducePartA();

    Product1* p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:\n";
    builder->ProducePartA();
    builder->ProducePartB();
    builder->ProducePartC();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main() {
    ClientCode();
    return 0;
}