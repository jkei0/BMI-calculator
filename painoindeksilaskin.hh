// Joni Keinänen
// 267144
// joni.keinanen@student.tut.fi

// Moduulissa esitellään käyttöliittymän
// käyttämät funktiot ja itse käyttöliittymä

#ifndef PAINOINDEKSILASKIN_HH
#define PAINOINDEKSILASKIN_HH

#include <QMainWindow>
#include <QActionGroup>

namespace Ui {
class Painoindeksilaskin;
}

class Painoindeksilaskin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Painoindeksilaskin(QWidget *parent = 0);
    ~Painoindeksilaskin();

public slots:
    void laske_bmi();
    void paivita_tulkinta(double BMI);
    void paivita_kayttoliittyma(double BMI);
    void alusta();

private:
    Ui::Painoindeksilaskin *ui;

    // luodaan QAction group luokka, jolla saadaan asetettua
    // sukupuolivalikko sellaiseksi, että vain toinen voi olla
    // valittuna
    QActionGroup *sukupuolivalikko = new QActionGroup(this);
};

#endif // PAINOINDEKSILASKIN_HH
