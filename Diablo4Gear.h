#include <QComboBox>
#include <QList>
#include <QStringList>
#include <QWidget>

namespace Ui {
class Diablo4Gear;
}

class Diablo4Gear : public QWidget {
    Q_OBJECT

  public:
    explicit Diablo4Gear(QWidget* parent = nullptr);
    virtual ~Diablo4Gear() override;

  protected:
    void clearAffixes();
    void clearReferences();
    void clearEquipements();

    void setReferences(const QStringList affixes);
    void setEquipements(const QStringList affixes);
    void setComboBox(QComboBox* comboBox, const QStringList affixes);
    void setScore(int score);

    QStringList getAffixes() const;
    QList<QComboBox*> getReferences() const;
    QList<QComboBox*> getPriorities() const;
    QList<QComboBox*> getEquipements() const;
    int getScore() const;

  protected slots:
    void on_plainTextEditAffixes_textChanged();
    void on_comboBoxEquipement1_currentIndexChanged(int index);
    void on_comboBoxEquipement2_currentIndexChanged(int index);
    void on_comboBoxEquipement3_currentIndexChanged(int index);

  private:
    Ui::Diablo4Gear* _ui{nullptr};
};
