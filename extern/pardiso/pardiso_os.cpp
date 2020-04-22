#include <pardiso_os.h>
#include <iostream>

#define STRINGIFY(s) #s
#define PARDISO_FILENAME(s) STRINGIFY(s)

/*extern "C" void pardisoinit (void   *, int    *,   int *, int *, double *, int *);
extern "C" void pardiso     (void   *, int    *,   int *, int *,    int *, int *,
double *, int    *,    int *, int *,   int *, int *,
int *, double *, double *, int *, double *);
extern "C" void pardiso_chkmatrix  (int *, int *, double *, int *, int *, int *);
extern "C" void pardiso_chkvec     (int *, int *, double *, int *);
extern "C" void pardiso_printstats (int *, int *, double *, int *, int *, int *,
double *, int *);*/

#include <dlfcn.h>


pardiso_os::Pardiso::Pardiso() {

    //load dynamic libraries
    
    //osx
    m_pardiso_lib = dlopen(PARDISO_FILENAME(BARTELS_PARDISO_FILENAME),RTLD_LOCAL|RTLD_LAZY);
    
    if (!m_pardiso_lib) {
        printf("[%s] Unable to load library: %s\n", __FILE__, dlerror());
        exit(EXIT_FAILURE);
    }

     m_init = (pardisoinit *)dlsym(m_pardiso_lib, "pardisoinit");
     m_command = (pardisocommand *)dlsym(m_pardiso_lib, "pardiso");

    //windows TODO
    
    //linux TODO

}

pardiso_os::Pardiso::~Pardiso() {

    dlclose(m_pardiso_lib);
}

void pardiso_os::Pardiso::init(void   *a, int    *b,   int *c, int *d, double *e, int *f) const {
    
    m_init(a,b,c,d,e,f);

}

void pardiso_os::Pardiso::command(const void   *a, const int    *b,  const  int *c, const int *d,    const int *e, const int *f,
double *g, int    *h,    int *i, int *j,   int *k, int *l,
int *m, double *n, double *o, int *p, double *q) const {
    m_command(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q);
}