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
* Builder sýnýfýnda parça üretimi için kullanýlacak metodlar belirtildi.
*/
class Builder {
public:
    virtual ~Builder() {}
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};
/*
 * ConcreteBuilder1 sýnýfý yapým iþlemi için gerekli uygulamalarý saðlar.
 * Farklý þekillerde çalýþan birden fazla builder sýnýfý bulunabilir.
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
     *ConcreteBuilder'lar kendi metodlarýný saðlayacaklar.
     *Bu yüzden farklý arayüzlere sahip,
     *farklý builderlardan üretilmiþ farklý ürünler elde edilecek.
     */

    Product1* GetProduct() {
        Product1* result = this->product;
        this->Reset();
        return result;
    }
};

/**
 * ClientCode bir builder nesnesi yaratýyor.
 * Sonrasýnda build süreci baþlýyor(yapým süreci)
 * Daha sonra dönüþ Builder nesnesinden alýnýyor.
 */

 //Bu kýsým üzerinde deðiþiklik yapýldý//
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