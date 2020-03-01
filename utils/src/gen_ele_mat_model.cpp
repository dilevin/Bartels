#include <iostream>
#include <tuple>
#include <fstream>
#include <string>
#include <json.hpp>

#include <cstdio> 

#define STRINGIFY(s) #s
#define JsonDir(s) STRINGIFY(s)
#define SourceDir(s) STRINGIFY(s)

bool gen_energy, gen_grad, gen_hessian;

//Why oh why doesn't C++ have an std::path_seperator ? 
#ifdef _WIN32
    const std::string pathsep("\");
#else
    const std::string pathsep("/");
#endif

inline std::string json_dir() {
        return std::string(JsonDir(JSON_DIRECTORY))+"";
}


inline std::string source_dir() {
        return std::string(SourceDir(BARTELS_SRC_DIRECTORY))+"";
}

void write_energy_tet_files(std::string output_dir, std::string template_hpp, std::string template_cpp, std::string ele_type_name, std::string material_name, std::string qe, std::string B, std::string F) {

    std::string psi = "psi_"+material_name+"_F";

    std::string hpp_name =  output_dir+pathsep+"include"+pathsep+ele_type_name+"_"+material_name+"_"+"q.h";
    std::string cpp_name =  output_dir+pathsep+"src"+pathsep+ele_type_name+"_"+material_name+"_"+"q.cpp";

    FILE *fptr = fopen(hpp_name.c_str(), "w"); 
    fprintf(fptr, template_hpp.c_str(), (ele_type_name+material_name+"_q").c_str(), (ele_type_name+material_name+"_q").c_str(), psi.c_str(), ele_type_name.c_str(), material_name.c_str(), "q", (ele_type_name+"_"+material_name+"_q.cpp").c_str());
    fclose(fptr);

    fptr = fopen(cpp_name.c_str(), "w"); 
    fprintf(fptr,template_cpp.c_str(), ele_type_name.c_str(), material_name.c_str(), "q", ele_type_name.c_str(), material_name.c_str(), "q", qe.c_str(), B.c_str(), psi.c_str(), F.c_str());
    fclose(fptr);

}

void write_energy_tetmesh_files(std::string output_dir, std::string template_hpp, std::string template_cpp, std::string ele_type_name, std::string material_name, unsigned int num_dofs, unsigned int size_dofs) {

    std::string function_name = ele_type_name+"mesh_"+material_name+"_q";
    std::string tet_function_name = ele_type_name+"_"+material_name+"_q";
    
    std::string hpp_name =  output_dir+pathsep+"include"+pathsep+function_name+".h";
    std::string cpp_name =  output_dir+pathsep+"src"+pathsep+function_name+".cpp";

    //include file
    FILE *fptr = fopen(hpp_name.c_str(), "w"); 
    fprintf(fptr, template_hpp.c_str(), function_name.c_str(), function_name.c_str(), tet_function_name.c_str(), function_name.c_str(), function_name.c_str());
    fclose(fptr);

    //cpp
    fptr = fopen(cpp_name.c_str(), "w"); 
    fprintf(fptr, template_cpp.c_str(), function_name.c_str(), function_name.c_str(), tet_function_name.c_str(), num_dofs, size_dofs);
    fclose(fptr);

}

//return filenames you wrote out
void write_tet_files(std::string output_dir, std::string template_hpp, std::string template_cpp, std::string ele_type_name, std::string material_name, std::string qe, std::string B, std::string F, std::string dF, std::string dpsi, std::string output, std::string dd) {
    
     std::string hpp_name =  output_dir+pathsep+"include"+pathsep+ele_type_name+"_"+material_name+"_"+dd+".h";
     std::string cpp_name =  output_dir+pathsep+"src"+pathsep+ele_type_name+"_"+material_name+"_"+dd+".cpp";

    FILE *fptr = fopen(hpp_name.c_str(), "w"); 
    fprintf(fptr, template_hpp.c_str(), (ele_type_name+material_name+"_"+dd).c_str(), (ele_type_name+material_name+"_"+dd).c_str(), dpsi.c_str(), ele_type_name.c_str(), material_name.c_str(), dd.c_str(), (ele_type_name+"_"+material_name+"_"+dd+".cpp").c_str());
    fclose(fptr);

    fptr = fopen(cpp_name.c_str(), "w"); 
    fprintf(fptr,template_cpp.c_str(), ele_type_name.c_str(), material_name.c_str(), dd.c_str(), ele_type_name.c_str(), material_name.c_str(), dd.c_str(), qe.c_str(), B.c_str(), dF.c_str(), dpsi.c_str(), F.c_str(), output.c_str());
    fclose(fptr);
}

void write_gradient_tet_files(std::string output_dir, std::string template_hpp, std::string template_cpp, std::string ele_type_name, std::string material_name, std::string qe, std::string B, std::string F) {

    std::string dF_type = "Eigen::Vector9x";
    std::string dpsi = "dpsi_"+material_name+"_dF";
    std::string output = "B.transpose()*dF";
    
    write_tet_files(output_dir, template_hpp, template_cpp, ele_type_name, material_name, qe, B, F, dF_type, dpsi, output, "dq");

}

//return filenames you wrote out 
void write_hessian_tet_files(std::string output_dir, std::string template_hpp, std::string template_cpp, std::string ele_type_name, std::string material_name, std::string qe, std::string B, std::string F) {

    std::string dF_type = "Eigen::Matrix9x";
    std::string dpsi = "d2psi_"+material_name+"_dF2";
    std::string output = "B.transpose()*dF*B";
    
    write_tet_files(output_dir, template_hpp, template_cpp, ele_type_name, material_name, qe, B, F, dF_type, dpsi, output, "dq2");

}

//write out the mesh files 
void write_mesh_files(std::string output_dir, std::string template_hpp, std::string template_cpp, std::string ele_type_name, std::string material_name, std::string dd, std::string output_type, std::string tmp_storage, unsigned int num_dofs, unsigned int size_dofs) {

    std::string function_name = ele_type_name+"mesh_"+material_name+"_"+dd;
    std::string tet_function_name = ele_type_name+"_"+material_name+"_"+dd;
    
    std::string hpp_name =  output_dir+pathsep+"include"+pathsep+function_name+".h";
    std::string cpp_name =  output_dir+pathsep+"src"+pathsep+function_name+".cpp";

    //include file
    FILE *fptr = fopen(hpp_name.c_str(), "w"); 
    fprintf(fptr, template_hpp.c_str(), function_name.c_str(), function_name.c_str(), tet_function_name.c_str(), function_name.c_str(), output_type.c_str(), function_name.c_str());
    fclose(fptr);

    //cpp
    fptr = fopen(cpp_name.c_str(), "w"); 
    fprintf(fptr, template_cpp.c_str(), function_name.c_str(), function_name.c_str(), output_type.c_str(), tet_function_name.c_str(), num_dofs, size_dofs, tmp_storage.c_str());
    fclose(fptr);
    

}

void write_gradient_tetmesh_files(std::string output_dir, std::string template_hpp, std::string template_cpp, std::string ele_type_name, std::string material_name, unsigned int num_dofs, unsigned int size_dofs) {

    write_mesh_files(output_dir, template_hpp, template_cpp, ele_type_name, material_name, "dq", "Eigen::VectorXx<DerivedRet>", "Eigen::Vector"+std::to_string(num_dofs*size_dofs)+"x<DerivedRet>", num_dofs, size_dofs);

}

void write_hessian_tetmesh_files(std::string output_dir, std::string template_hpp, std::string template_cpp, std::string ele_type_name, std::string material_name, unsigned int num_dofs, unsigned int size_dofs) {

    write_mesh_files(output_dir, template_hpp, template_cpp, ele_type_name, material_name, "dq2", "Eigen::SparseMatrix<DerivedRet>", "Eigen::Matrix"+std::to_string(num_dofs*size_dofs)+"x<DerivedRet>", num_dofs, size_dofs);

}

int main(int argc, char **argv) {

    using json = nlohmann::json;

    gen_energy = gen_grad = gen_hessian = true;

    if(argc < 3) {
        std::cout<<"Not enough arguments\n";
        exit(0);
    }

    //partial build, check what's what
    if(argc > 3) {
        gen_energy = gen_grad = gen_hessian = false;

        if(strcmp(argv[3], "energy") ==  0) {
            gen_energy = true;
        } else if(strcmp(argv[3], "gradient") == 0) {
            gen_grad = true;
        } else if(strcmp(argv[3], "hessian") == 0) {
            gen_hessian = true;
        }
    }

    //element name and type 
    std::string ele_type_name = argv[1];
    std::string material_name = argv[2];
    //material name to get the dF2 for

    //which files to generate 
    //1. energy
    //2. gradient
    //3. hessian

    //template json file with my C++ code
    //json file
    std::ifstream t(json_dir()+pathsep+"template_cpp.txt");
    std::string template_cpp((std::istreambuf_iterator<char>(t)),
    std::istreambuf_iterator<char>());

    std::ifstream t1(json_dir()+pathsep+"template_hpp.txt");
    std::string template_hpp((std::istreambuf_iterator<char>(t1)),
    std::istreambuf_iterator<char>());

    std::ifstream t2(json_dir()+pathsep+"template_mesh_cpp.txt");
    std::string template_mesh_cpp((std::istreambuf_iterator<char>(t2)),
    std::istreambuf_iterator<char>());

    std::ifstream t3(json_dir()+pathsep+"template_mesh_hpp.txt");
    std::string template_mesh_hpp((std::istreambuf_iterator<char>(t3)),
    std::istreambuf_iterator<char>());

    std::ifstream t4(json_dir()+pathsep+"template_en_cpp.txt");
    std::string template_en_cpp((std::istreambuf_iterator<char>(t4)),
    std::istreambuf_iterator<char>());

    std::ifstream t5(json_dir()+pathsep+"template_en_hpp.txt");
    std::string template_en_hpp((std::istreambuf_iterator<char>(t5)),
    std::istreambuf_iterator<char>());

    std::ifstream t6(json_dir()+pathsep+"template_mesh_en_cpp.txt");
    std::string template_mesh_en_cpp((std::istreambuf_iterator<char>(t6)),
    std::istreambuf_iterator<char>());

    std::ifstream t7(json_dir()+pathsep+"template_mesh_en_hpp.txt");
    std::string template_mesh_en_hpp((std::istreambuf_iterator<char>(t7)),
    std::istreambuf_iterator<char>());

    //element specific (load from json)
    std::ifstream i(json_dir()+pathsep+ele_type_name+".json");
    json j;
    i >> j;
    std::string qe = j["qe"]; 
    std::string B = j["B"];
    std::string F = j["F"];

    unsigned int num_dofs = j["num_dofs"];
    unsigned int size_dofs = j["size_dofs"];

    //energy stuff
    if(gen_energy) {
        write_energy_tet_files(source_dir(), template_en_hpp, template_en_cpp, ele_type_name, material_name, qe, B, F);
        write_energy_tetmesh_files(source_dir(), template_mesh_en_hpp, template_mesh_en_cpp, ele_type_name, material_name, num_dofs, size_dofs);
    }

    //gradient stuff
    if(gen_grad) {
        write_gradient_tet_files(source_dir(), template_hpp, template_cpp, ele_type_name, material_name, qe, B,F);
        write_gradient_tetmesh_files(source_dir(), template_mesh_hpp, template_mesh_cpp, ele_type_name, material_name, num_dofs, size_dofs);
    }

    //hessian stuff
    if(gen_hessian) {
        write_hessian_tet_files(source_dir(), template_hpp, template_cpp, ele_type_name, material_name, qe, B, F);
        write_hessian_tetmesh_files(source_dir(), template_mesh_hpp, template_mesh_cpp, ele_type_name, material_name, num_dofs, size_dofs);
    }

    std::cout<<"Files written to: "<<source_dir()<<"\n";
    
}