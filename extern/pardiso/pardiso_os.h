#ifndef PARDISO_OS_H
#define PARDISO_OS_H

namespace pardiso_os {

    class Pardiso {

        public:

            Pardiso();
            ~Pardiso();

            void init(void   *, int    *,   int *, int *, double *, int *) const;
    
            void command(const void   *a, const int    *b,   const int *c, const int *d,    const int *e, const int *f,
                    double *g, int    *h,    int *i, int *j,   int *k, int *l,
                    int *m,  double *n, double *o, int *p, double *q) const;

        private:
            
            typedef void pardisoinit(void   *, int    *,   int *, int *, double *, int *);
            typedef void pardisocommand(const void   *a, const int    *b,   const int *c, const int *d,    const int *e, const int *f,
                                 double *g, int    *h,    int *i, int *j,   int *k, int *l,
                                 int *m, double *n, double *o, int *p, double *q);

            void * m_pardiso_lib;
            pardisoinit *m_init;
            pardisocommand *m_command;

    };
}

 #endif