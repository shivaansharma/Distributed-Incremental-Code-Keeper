#include "dependencies.hpp"

commands match (std :: string input){
    if(input == "add") return commands :: add;
    else if(input == "cat-file") return commands :: catFile;
    else if(input == "check-ignore") return commands :: checkIgnore;
    else if(input == "checkout") return commands :: checkout;
    else if(input == "commit") return commands :: commit;
    else if(input == "hash-object") return commands :: hashObject;
    else if(input == "init") return commands :: init;
    else if(input == "log") return commands :: log;
    else if(input == "ls-files") return commands :: lsFiles;
    else if(input == "ls-tree") return commands :: lsTree;
    else if(input == "rev-parse") return commands :: revParse;
    else if(input == "rm") return commands :: rm;
    else if(input == "show-ref") return commands :: showRef;
    else if(input == "status") return commands :: status;
    else if(input == "tag") return commands :: tag;
    else return commands :: BAD_COMMAND;
}
objectType matchType(std :: string input){
    if(input == "blob"){
        return objectType :: BLOB;
    }else if (input == "tag"){
        return objectType :: TAG;
    }else if (input == "commit"){
        return objectType :: COMMIT;
    }else if(input == "tree"){
        return objectType :: TREE;
    }else {
        return objectType :: BADTYPE;
    }
}
int main(int argc ,char* argv[]){
    std :: cout<<argc ;
    if(argc < 2){
        Errors ::fatal("No commands passed");
    }
    commands matched = match (argv[1]);
    switch (matched)
    {
    case commands :: add :
        Errors :: dBug("add Called");
        break;
    case commands::catFile: {
    if (argc < 4) {
        Errors::fatal("format: ./src catFile <type> <hash/object>");
    }

    std::string typeStr = argv[2];

    if (typeStr == "help") {
        std::cout << "format: ./src catFile <type> <hash/object>\n";
        std::exit(EXIT_SUCCESS);
    }

    objectType type = matchType(typeStr);
    if (type == objectType::BADTYPE) {
        Errors::fatal("wrong type");
    }

    std::string hash = argv[3];

    // repo find
    auto repoOpt = repoFind();
    if (!repoOpt.has_value()) {
        Errors::fatal("not a git repository");
    }

    // 🔥 ACTUALLY CALL catFile
   OBJECTHELPER ::catFile(repoOpt.value(),hash);

    break;
}

    case commands :: checkIgnore :
        Errors :: dBug("checkIgnore Called");
        break;
    case commands :: checkout :
        Errors :: dBug("checkout Called");
        break;
    case commands :: commit :
        Errors :: dBug("commit Called");
        break;
    case commands::hashObject: {
    if (argc < 5)
        Errors::fatal("usage: hash-object [-w] -t TYPE FILE");

    bool write = false;
    int i = 2;

    // optional -w
    if (std::string(argv[i]) == "-w") {
        write = true;
        i++;
    }

    // must be -t
    if (std::string(argv[i]) != "-t")
        Errors::fatal("usage: hash-object [-w] -t TYPE FILE");
    i++;

    if (i >= argc)
        Errors::fatal("missing object type");

    objectType obj = matchType(argv[i]);
    if (obj == objectType::BADTYPE)
        Errors::fatal("object not supported");
    i++;

    if (i >= argc)
        Errors::fatal("missing file");

    std::filesystem::path path{argv[i]};

    OBJECTHELPER::cmdHashFile(path, obj, write);

    Errors::dBug("hashObject Called");
    break;
}

case commands::init: {
    if (argc < 3) {
        Errors::fatal("The path was not passed");
    }

    // Check if the user is asking for help at argv[2]
    std::string arg2 = argv[2];
    if (arg2 == "-help") {
        std::cout << "Usage: init <path_to_repo>" << std::endl;
        break; // Exit the case early
    }

    // If not help, proceed with the path
    std::filesystem::path p{arg2};
    repoCreate(p);
    Errors::dBug("init Called");
    break;
}
    case commands :: log :
        Errors :: dBug("log Called");
        break;
    case commands :: lsFiles :
        Errors :: dBug("lsFiles Called");
        break;
    case commands :: lsTree :
        Errors :: dBug("lsTree Called");
        break;
    case commands :: revParse :
        Errors :: dBug("revParse Called");
        break;
    case commands :: rm :
        Errors :: dBug("rm Called");
        break;
    case commands :: showRef :
        Errors :: dBug("showRef Called");
        break;
    case commands :: status :
        Errors :: dBug("status Called");
        break;
    case commands :: tag :
        Errors :: dBug("tag Called");
        break;
    default:
        Errors :: fatal(" Bad_command encountured ");
        break;
    }
}