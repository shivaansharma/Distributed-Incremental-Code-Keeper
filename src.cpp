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
    case commands :: catFile :{
        if(argc<4){
            Errors ::fatal("command error , format : ./src catFile <Type> <hash / object>");
        }
        if(argv[2] == "help"){
            std :: cout<<" format : ./src catFile <Type> <hash / object>";
            std :: exit(EXIT_FAILURE);
        }
        objectType type {matchType(argv[2])};
        if(type == objectType :: BADTYPE){
            Errors :: fatal("wrong type");
        }
        std :: string hash_160_bit{argv[3]};
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
    case commands :: hashObject :
        Errors :: dBug("hashObject Called");
        break;
    case commands :: init :{
        if(argc < 3) Errors :: fatal("The path was not passed");
        if(argv[3] == "help") std :: cout<<"enter the path to make an empty repo";
        std :: filesystem :: path p {argv[2]};
        REPOHELPER :: repoCreate(p);
        Errors :: dBug("init Called");
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