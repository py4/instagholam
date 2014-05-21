#include <QPushButton>
#include <string>

class RequestButton : public QPushButton
{
    Q_OBJECT
    //Q_PROPERTY( QString m_sServiceName READ getServiceName WRITE setServiceName DESIGNABLE true );
    //Q_PROPERTY( float m_fPrice READ getPrice WRITE setPrice DESIGNABLE true );
public:
    RequestButton(QWidget *parent = 0);
    RequestButton(std::string,QWidget *parent = 0);
//public slots:
//   QString     getServiceName();
//    void        setServiceName( QString s );
 //   float       getPrice();
 //   void        setPrice( float f );
//protected:
public:
    std::string username;
    //QString     m_sServiceName;
    //float       m_fPrice;
};