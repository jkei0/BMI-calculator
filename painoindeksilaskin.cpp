// Joni Keinänen
// 267144
// joni.keinanen@student.tut.fi


// Moduulissa luodaan yhteydet käyttöliittymä widgettien välille
// ja määritellään funktiot, joita käyttöliittymä käyttää

#include "painoindeksilaskin.hh"
#include "ui_painoindeksilaskin.h"


Painoindeksilaskin::Painoindeksilaskin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Painoindeksilaskin)
{
    ui->setupUi(this);

    // Aktivoituu kun painoa muutetaan
    connect(ui->spinBox_paino, SIGNAL(valueChanged(int)),
            this, SLOT(laske_bmi()));

    // Aktivoituu, kun pituutta muutetaan
    connect(ui->spinBox_pituus, SIGNAL(valueChanged(int)),
            this, SLOT(laske_bmi()));

    // Aktivoituu, kun menusta valitaan alkutila
    connect(ui->action_alkutila, SIGNAL(triggered(bool)),
            this, SLOT(alusta()));

    // Lopettaa ohjelman, kun menusta valitaan lopeta
    connect(ui->action_lopeta, SIGNAL(triggered(bool)),
            this, SLOT(close()));

    // Aktivoituu, kun menusta valitaan sukupuoleksi mies
    connect(ui->action_mies, SIGNAL(triggered(bool)),
            this, SLOT(laske_bmi()));

    // Aktivoituu, kun valitaan sukupuoleksi nainen
    connect(ui->action_nainen, SIGNAL(triggered(bool)),
            this, SLOT(laske_bmi()));

    // Tehdään sukupuoli-menusta sellainen, että vain toinen
    // sukupuoli voi olla valittuna
    sukupuolivalikko->setExclusive(true);
    sukupuolivalikko->addAction(ui->action_mies);
    sukupuolivalikko->addAction(ui->action_nainen);

}

Painoindeksilaskin::~Painoindeksilaskin()
{
    delete sukupuolivalikko;
    delete ui;    
}

void Painoindeksilaskin::paivita_tulkinta(double BMI) {
// Funktio päivittää tulkinta kenttään tiedon siitä,
// mihin painoluokkaan annettu BMI kuuluu

    // Jos menusta on valittu sukupuoleksi mies, niin
    // tulkitaan BMI:tä miehen viitearvojen mukaan
    if ( ui->action_mies->isChecked()) {

        if ( BMI <= 20.7 ) {
            ui->label_tulkinta->setText("alipainoa");
        }

        else if ( (BMI > 20.7) and (BMI <= 26.4) ) {
            ui->label_tulkinta->setText("normaali");
        }

        else if ( (BMI > 26.4) and (BMI <= 27.8) ) {
            ui->label_tulkinta->setText("lievää ylipainoa");
        }

        else if ( (BMI > 27.8) and (BMI <= 31.1) ) {
            ui->label_tulkinta->setText("ylipainoa");
        }

        else {
            ui->label_tulkinta->setText("paljon ylipainoa");
        }
    }

    // Jos nainen valittuna niin tulkitaan
    // BMI:tä naisten viitearvojen mukaan
    if ( ui->action_nainen->isChecked() ) {

        if ( BMI <= 19.1 ) {
            ui->label_tulkinta->setText("alipainoa");
        }

        else if ( (BMI > 19.1) and (BMI <= 25.8) ) {
            ui->label_tulkinta->setText("normaali");
        }

        else if ( (BMI > 25.8) and (BMI <= 27.3) ) {
            ui->label_tulkinta->setText("lievää ylipainoa");
        }

        else if ( (BMI > 27.3) and (BMI <= 32.2) ) {
            ui->label_tulkinta->setText("ylipainoa");
        }

        else {
            ui->label_tulkinta->setText("paljon ylipainoa");
        }
    }
}

void Painoindeksilaskin::paivita_kayttoliittyma(double BMI) {
// Funktio päivittää käyttöliittymään näkyviin uuden BMI:n
// sekä sen, onko henkilö ali- yli- vai normaalipainoinen
// sekä henkilön sukupuolen
// Parametri: henkilön BMI

    // Päivitetään sukupuolen kertovan teksti-labelin
    // teksti kuvaamaan menusta valittua sukupuolta
    if (ui->action_mies->isChecked()) {
        ui->label_sukupuoli->setText("mies");
    }    
    else {
        ui->label_sukupuoli->setText("nainen");
    }

    // ERIKOISTAPAUS: jos BMI:ksi on annettu nolla, niin
    // asetetaan BMI:n sekä sen tulkinnan ilmoittamat teksti-
    // labelit viivoiksi
    if ( BMI == 0 ) {
        ui->label_painoindeksi->setText("-");
        ui->label_tulkinta->setText("-");
    }

    // Muuten asetetaan BMI sen ilmoittamaan teksti-labeliin
    // ja kutsutaan tulkinta-labelin päivittävää funktiota
    else {

        // muutetaan Qnumber Qstringgiksi
        QString painoindeksi = QString::number(BMI);

        ui->label_painoindeksi->setText(painoindeksi);
        paivita_tulkinta(BMI);
    }
}


void Painoindeksilaskin::laske_bmi() {
// Funktio laskee BMI:n

    // ERIKOISTAPAUS: jos paino tai pituus on nollassa
    // päivitetään käyttöliittymä olettaen, että BMI on 0
    // ja lopetetaan funktion suorittaminen
    if ( ui->spinBox_paino->value() == 0 or
         ui->spinBox_pituus->value() == 0 ) {

        paivita_kayttoliittyma(0);
        return;
    }

    // Haetaan paino ja pituus, joka muutetaan metreiksi ja
    // lasketaan BMI, jonka jälkeen päivitetään käyttöliittymä
    double BMI = 0;
    int paino = ui->spinBox_paino->value();
    double pituus = ui->spinBox_pituus->value() / 100.0;

    BMI = paino/(pituus*pituus);

    paivita_kayttoliittyma(BMI);
}

void Painoindeksilaskin::alusta() {
// Funktio palauttaa käyttöliittymän
// alkutilaan

    ui->spinBox_paino->setValue(0);
    ui->spinBox_pituus->setValue(0);
    ui->action_nainen->setChecked(true);
    paivita_kayttoliittyma(0);
}
