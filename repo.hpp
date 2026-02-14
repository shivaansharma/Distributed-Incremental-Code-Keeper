#ifndef REPO_H
#define REPO_H
#include<iostream>
#include<filesystem>
#include "inih/cpp/INIReader.h"
#include "errors.hpp"
#include <fstream>
// repo is a combination of a work tree and a git dir
// we need to create a repo
// the .git dir contains objects/ , refs/ , HEAD , config , description
// createRepo(path) // creates the repo

//createPath (repo , path) takes the repo and generays a std :: filesystem :: path object  
//done
// repo_file () // if repo Files do not exist it creates if exist returns the existing  
//maybe it will be void 
//will not be void 
// repo_dir () // if dir .git file does not exist it will make one or else it will return the existing one 

//repo create will create a repo and return path


class Repo;
template<typename... Parts>
std::filesystem::path repoPath(Repo& repo, Parts... parts);

template<typename... Parts>
std::optional<std::filesystem::path> repoDir(Repo& repo, bool makeDir, Parts... parts);

template<typename... Parts>
std::filesystem::path repoFile(Repo& repo, Parts... parts);

std::string repoDefaultConfig();

class Repo {
    public :
    std :: filesystem :: path workTree ;
    std :: filesystem :: path gitDir;
    INIReader conf;

    
    Repo(std :: string path , bool force = false)
    :
    workTree{std :: filesystem :: path (path)},
    gitDir{std :: filesystem :: path (path)/".git"},
    conf("")
    {
        if(! std :: filesystem :: is_directory(workTree)){
            Errors::fatal("File Does not exist");
        }
        if (!(force || std::filesystem::is_directory(gitDir))) {
            Errors::fatal("Not a Git repository: " + path);
        }
        std :: filesystem :: path cf = repoFile(*this,"config");
        if (std::filesystem::exists(cf)) {
            conf = INIReader(cf.string());

            if (conf.ParseError() != 0) {
                Errors::fatal("Failed to parse config file");
            }
        }
        else if (!force) {
            Errors::fatal("Configuration file missing");
        }
        if (!force) {
            int vers = conf.GetInteger("core", "repositoryformatversion", -1);
            if (vers != 0) {
                Errors::fatal("Unsupported repositoryformatversion: " + std::to_string(vers));
            }
        }
    }
};


template<typename...Parts>
std :: filesystem :: path repoPath (Repo &repo ,Parts ...parts){
    std :: filesystem :: path p = repo.gitDir;    //creates path
    ((p/=parts),...);
    return p;
}
template<typename ...Parts>
std :: filesystem :: path  repoFile(Repo &repo ,Parts ...parts){    //checks if a file path exists if no creates one
    return repoPath(repo,parts...);
}
template<typename ...Parts>
std :: optional<std :: filesystem :: path>  repoDir(Repo &repo , bool makeDir ,Parts ...parts ){    //checks if a file path exists if no creates one

    std :: filesystem :: path p = repoPath(repo,parts...);

    if(std :: filesystem :: exists(p)){
        if(std :: filesystem :: is_directory(p)) return p;

        else {
            Errors :: fatal ("the directory is not vaid ");
        }
    }
    else {

        Errors :: warning ("The file Path Does not Exist the system will now create one for u" + p.string());

       if(makeDir){
        std :: filesystem :: create_directories(p);

       return p;
       }
        return std :: nullopt;
       

    }
}

    
std :: filesystem :: path repoCreate (std :: filesystem :: path path){
    //check if the repo exists 
    // check for directory 
    if (std::filesystem::exists(path)) {
        if (!std::filesystem::is_directory(path)) {
            Errors::fatal("Path is not a directory");
        }
    if (!std::filesystem::is_empty(path)) {
        Errors::fatal("Directory is not empty");
    }
    } else {
        std::filesystem::create_directories(path);
    }

     std::filesystem::create_directories(path / ".git");
     Repo repo {path,true};
    repoDir(repo,true,"branches");
    repoDir(repo,true,"objects");
    repoDir(repo,true,"refs","tags");
    repoDir(repo,true,"refs","heads");

    std :: ofstream outRepo (repoFile(repo,"description"));

    if(!outRepo) Errors :: fatal ("error in opening file");

    outRepo <<"Unnamed repository; edit this file 'description' to name the repository.\n";

    outRepo.close();

    std :: ofstream outHead (repoFile(repo,"HEAD"));

    if(!outHead) Errors :: fatal ("error in opening file");

    outHead << "ref: refs/heads/master\n";

    outHead.close();

    std :: ofstream outConfig (repoFile(repo,"config"));

    if(!outConfig) Errors :: fatal ("error in opening file");

    outConfig << repoDefaultConfig();

    outConfig.close();

    return path;
}

std::string repoDefaultConfig() {
    return
        "[core]\n"
        "\trepositoryformatversion = 0\n"
        "\tfilemode = true\n"
        "\tbare = false\n";
}
std :: optional<Repo> repoFind(std :: filesystem :: path p = "." , bool req = true){
    std :: filesystem :: path fullPath {std :: filesystem :: canonical(p)};
    if(std :: filesystem :: is_directory(fullPath/".git")) return Repo(fullPath);


     std :: filesystem :: path parent {std :: filesystem :: canonical(p/"..")};

     if(parent == fullPath){
        if(req){
            Errors :: fatal ("No git directory.");
        }else {
            return std :: nullopt;
        }
     }
     return repoFind(parent,req);
}

#endif