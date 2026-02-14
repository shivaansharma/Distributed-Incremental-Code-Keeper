#ifndef OBJECT_HELPERS_HPP
#define OBJECT_HELPERS_HPP
#include<variant>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <stdexcept>
#include <zlib.h>
class Repo;
namespace OBJECTHELPER {

inline std::string zlibDecompressFile(const std::filesystem::path& path)
{
    // 1️⃣ Read entire file
    std::ifstream file(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("cannot open file");

    std::string compressed(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    // 2️⃣ Setup zlib stream
    z_stream strm{};
    if (inflateInit(&strm) != Z_OK)
        throw std::runtime_error("inflateInit failed");

    strm.next_in  = reinterpret_cast<Bytef*>(compressed.data());
    strm.avail_in = static_cast<uInt>(compressed.size());

    // 3️⃣ Decompress
    std::string decompressed;
    char out[16384];

    int ret;
    do {
        strm.next_out  = reinterpret_cast<Bytef*>(out);
        strm.avail_out = sizeof(out);

        ret = inflate(&strm, Z_NO_FLUSH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            inflateEnd(&strm);
            throw std::runtime_error("inflate failed");
        }

        decompressed.append(out, sizeof(out) - strm.avail_out);

    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);
    return decompressed;
}

inline std::variant<GitBlob,GitTag,GitTree,GitCommit> objectRead(Repo repo, const std::string& shaHash)
{
    std::string dir  = shaHash.substr(0, 2);
    std::string file = shaHash.substr(2);

    std::filesystem::path path = repoPath(repo, "objects", dir, file);

    if (!std::filesystem::exists(path))  Errors::fatal("path does not exist");

    std::string raw = zlibDecompressFile(path);

    auto spaceIt = std::find(raw.begin(), raw.end(), ' ');
    if (spaceIt == raw.end())
        Errors::fatal("malformed object");

    std::string fmt(raw.begin(), spaceIt);

    auto nullIt = std::find(spaceIt + 1, raw.end(), '\0');
    if (nullIt == raw.end())
        Errors::fatal("malformed object");

    size_t size = std::stoul(std::string(spaceIt + 1, nullIt));
    if (size != static_cast<size_t>(raw.end() - (nullIt + 1)))
        Errors::fatal("bad object length");

    std::string payload(nullIt + 1, raw.end());

    if (fmt == "commit") Errors::fatal("call unimplemented commit");//return GitCommit(payload);
    if (fmt == "tree") Errors::fatal("call unimplemented tree"); // return GitTree(payload);
    if (fmt == "tag")  Errors::fatal("call unimplemented tag");  //return GitTag(payload);
    if (fmt == "blob")   return GitBlob(payload);

    Errors::fatal("unknown object type: " + fmt);
}

inline std :: string writeObject(GitObject& obj, Repo repo)
{
    std::string data = obj.serialize();

    std::string result;
    result.reserve(obj.fmt.size() + 1 + 20 + 1 + data.size());

    result += obj.fmt;
    result += ' ';
    result += std::to_string(data.size());
    result.push_back('\0');
    result += data;

    SHA shaObj(result);
    std::string sha = shaObj.getHash();

    std::string dir  = sha.substr(0, 2);
    std::string file = sha.substr(2);

    std::filesystem::path objDir =
        repoPath(repo, "objects", dir);

    std::filesystem::create_directories(objDir);

    std::filesystem::path objPath = objDir / file;

    if (std::filesystem::exists(objPath))
        return " ";

    // --- zlib compress ---
    uLongf outSize = compressBound(result.size());
    std::string compressed(outSize, '\0');

    int rc = compress(
        reinterpret_cast<Bytef*>(&compressed[0]), &outSize,
        reinterpret_cast<const Bytef*>(result.data()),
        result.size()
    );

    if (rc != Z_OK)
        Errors::fatal("zlib compress failed");

    compressed.resize(outSize);

    std::ofstream out(objPath, std::ios::binary);
    if (!out)
        Errors::fatal("cannot write object");

    out.write(compressed.data(), compressed.size());
    return sha;
}

std :: string findObject(Repo repo ,std :: string name){
    return name;
}   
void catFile(Repo r,std :: string name){
    auto obj {objectRead(r,findObject(r, name))};
    if (auto* blob = std::get_if<GitBlob>(&obj)) {
    std::cout << blob->serialize();
}
else if (auto* tree = std::get_if<GitTree>(&obj)) {
    Errors::fatal("tree not supported");
}
else if (auto* commit = std::get_if<GitCommit>(&obj)) {
    Errors::fatal("commit not supported");
}
else if (auto* tag = std::get_if<GitTag>(&obj)) {
    Errors::fatal("tag not supported");
}
}


void cmdCatFile(std :: string name){
    if(! repoFind().has_value()){
        Errors :: fatal("repoFind has no value");
    }
    Repo r =repoFind().value();
    catFile(r,name);
}
std::string objectHash(const std::filesystem::path& path,
                       objectType type,
                       Repo* repo)
{
    // read file
    std::ifstream f(path, std::ios::binary);
    if (!f) Errors::fatal("cannot open file");

    std::string data(
        (std::istreambuf_iterator<char>(f)),
         std::istreambuf_iterator<char>()
    );

    // create object (POLYMORPHIC)
    GitObject *obj = nullptr ;

    if      (type == objectType::BLOB)   obj = new  GitBlob(data);
    else if (type == objectType::TREE)   Errors::fatal("Unimplemented object tree");
    else if (type == objectType::COMMIT) Errors::fatal("Unimplemented object commit");
    else if (type == objectType::TAG)    Errors::fatal("Unimplemented object tag");
    else Errors::fatal("unknown object type");

    // hash + write
    std::string sha = writeObject(*obj, *repo);

    delete obj;   // important
    return sha;
}

void cmdHashFile(std::filesystem::path& path,
                 objectType type,
                 bool write)
{
    Repo* repo = nullptr;

    if (write) {
        auto repoOpt = repoFind();
        if (!repoOpt) Errors::fatal("not a git repository");
        repo = &*repoOpt;
    }

    std::cout << objectHash(path, type, repo) << '\n';
}



std :: string object_find(Repo r , std :: string name){
    return name;
}

}


#endif
