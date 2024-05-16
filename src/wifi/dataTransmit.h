#ifndef GBGAME_DATATRANSMIT_H
#define GBGAME_DATATRANSMIT_H


class DataTransmit {
public:
    static DataTransmit& getInstance(); // Static method to access the instance

    // Delete copy constructor and assignment operator
    DataTransmit(const DataTransmit&) = delete;
    DataTransmit& operator=(const DataTransmit&) = delete;

    void init();

private:
    DataTransmit();  // Private constructor
    ~DataTransmit(); // Private destructor if needed
};

#endif //GBGAME_DATATRANSMIT_H
