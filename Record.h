#ifndef RECORD_H
#define RECORD_H
//NOTE: ERROR WITH RECORD?
#include <string>
class Record {
    private:
        int id;
        std::string name;
        std::string addedBy;
    public:
        Record();
        Record(int id, std::string name, std::string addedBy);
        int getID() const;
        void setID(int id);
        std::string getName() const;
        std::string getAddedBy() const;
        void setName(std::string name);
        friend bool operator<(const Record& r1, const Record& r2);
        friend bool operator>(const Record& r1, const Record& r2);
        friend bool operator==(const Record& r1, const Record& r2);
        friend bool operator!=(const Record& r1, const Record& r2);

};
#endif 