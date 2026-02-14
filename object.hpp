#include "errors.hpp"

class GitObject {
public:
    std::string fmt;
    virtual ~GitObject() = default;

    virtual std::string serialize()  = 0;
    virtual void deserialize(std::string& data) = 0;
};


class GitBlob : GitObject{
    public :
    GitBlob(){
        fmt = "blob";
    }
    explicit GitBlob(std::string& data) {
        fmt = "blob";
        deserialize(data);
    }
    std :: string serialize () override{
        return blobData;
    }
    void deserialize(std::string& data) override {
        blobData = data;
    }
    private:
    std::string blobData;
};

class GitTag :GitObject{

};
class GitTree :GitObject{

};
class GitCommit :GitObject{

};