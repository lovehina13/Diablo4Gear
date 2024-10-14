#include "Diablo4Gear.h"
#include "ui_Diablo4Gear.h"

#include <QString>
#include <cmath>

Diablo4Gear::Diablo4Gear(QWidget* parent) : QWidget(parent), _ui(new Ui::Diablo4Gear) {
    _ui->setupUi(this);
}

Diablo4Gear::~Diablo4Gear() { delete _ui; }

void Diablo4Gear::clearAffixes() { _ui->plainTextEditAffixes->clear(); }

void Diablo4Gear::clearReferences() {
    QList<QComboBox*> references = getReferences();
    for (const auto& reference : references) {
        reference->clear();
    }
    QList<QComboBox*> priorities = getPriorities();
    for (const auto& priority : priorities) {
        priority->setCurrentIndex(0);
    }
}

void Diablo4Gear::clearEquipements() {
    QList<QComboBox*> equipements = getEquipements();
    for (const auto& equipement : equipements) {
        equipement->clear();
    }
    _ui->lineEditScore->clear();
}

void Diablo4Gear::setReferences(const QStringList affixes) {
    QList<QComboBox*> references = getReferences();
    for (const auto& reference : references) {
        setComboBox(reference, affixes);
    }
}

void Diablo4Gear::setEquipements(const QStringList affixes) {
    QList<QComboBox*> equipements = getEquipements();
    for (const auto& equipement : equipements) {
        setComboBox(equipement, affixes);
    }
}

void Diablo4Gear::setComboBox(QComboBox* comboBox, const QStringList affixes) {
    comboBox->addItem(QString("----------"));
    for (const auto& affixe : affixes) {
        comboBox->addItem(affixe);
    }
}

void Diablo4Gear::setScore(int score) {
    QString scoreText = QString::number(score);
    _ui->lineEditScore->setText(scoreText);
}

QStringList Diablo4Gear::getAffixes() const {
    QStringList affixes;
    QString plainText = _ui->plainTextEditAffixes->toPlainText();
    QStringList plainTextLines = plainText.split("\n");
    for (const auto& plainTextLine : plainTextLines) {
        QString simplifiedLine = plainTextLine.simplified();
        if (!simplifiedLine.isEmpty()) {
            affixes.append(simplifiedLine);
        }
    }
    return affixes;
}

QList<QComboBox*> Diablo4Gear::getReferences() const {
    QList<QComboBox*> references = {_ui->comboBoxReference1, _ui->comboBoxReference2,
                                    _ui->comboBoxReference3, _ui->comboBoxReference4,
                                    _ui->comboBoxReference5, _ui->comboBoxReference6};
    return references;
}

QList<QComboBox*> Diablo4Gear::getPriorities() const {
    QList<QComboBox*> priorities = {_ui->comboBoxPriority1, _ui->comboBoxPriority2,
                                    _ui->comboBoxPriority3, _ui->comboBoxPriority4,
                                    _ui->comboBoxPriority5, _ui->comboBoxPriority6};
    return priorities;
}

QList<QComboBox*> Diablo4Gear::getEquipements() const {
    QList<QComboBox*> equipements = {_ui->comboBoxEquipement1, _ui->comboBoxEquipement2,
                                     _ui->comboBoxEquipement3};
    return equipements;
}

int Diablo4Gear::getScore() const {
    int score = 0;
    QList<QComboBox*> references = getReferences();
    QList<QComboBox*> priorities = getPriorities();
    QList<QComboBox*> equipements = getEquipements();
    for (const auto& equipement : equipements) {
        QString equipementName = equipement->currentText();
        int referenceCount = 0;
        for (const auto& reference : references) {
            QString referenceName = reference->currentText();
            if (equipementName == referenceName && equipementName != "----------") {
                int priorityIndex = priorities.at(referenceCount)->currentIndex();
                score += std::pow(10, priorityIndex);
            }
            ++referenceCount;
        }
    }
    return score;
}

void Diablo4Gear::on_plainTextEditAffixes_textChanged() {
    QStringList affixes = getAffixes();
    clearReferences();
    clearEquipements();
    setReferences(affixes);
    setEquipements(affixes);
}

void Diablo4Gear::on_comboBoxEquipement1_currentIndexChanged(int index) {
    int score = getScore();
    setScore(score);
}

void Diablo4Gear::on_comboBoxEquipement2_currentIndexChanged(int index) {
    int score = getScore();
    setScore(score);
}

void Diablo4Gear::on_comboBoxEquipement3_currentIndexChanged(int index) {
    int score = getScore();
    setScore(score);
}
