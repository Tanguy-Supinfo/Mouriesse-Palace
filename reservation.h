#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation
{
    public:
        Reservation();
        Reservation(int clientId, std::string type, std::string clientName,
               std::string startDateTime, std::string endDateTime);
        Reservation(const Reservation &other);
        ~Reservation();

        int getId() const;
        int getClientId() const;
        std::string getType() const;
        std::string getName() const;
        std::string getStartDateTime() const;
        std::string getEndDateTime() const;

        void setClientId(const int clientId);
        void setType(const std::string type);
        void setName(const std::string clientName);
        void setStartDateTime(const std::string startDateTime);
        void setEndDateTime(const std::string endDateTime);

    private:
        int rId;
        int rClientId;
        std::string rType;
        std::string rClientName;
        std::string rStartDateTime;
        std::string rEndDateTime;

        void createId();

};

#endif // RESERVATION_H