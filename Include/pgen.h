#ifndef Py_PGEN_H
#define Py_PGEN_H
#ifdef __cplusplus
extern "C" {
#endif


/* Parser generator interface */

__attribute__ ((visibility ("default"))) extern grammar *meta_grammar(void);

struct _node;
__attribute__ ((visibility ("default"))) extern grammar *pgen(struct _node *);

#ifdef __cplusplus
}
#endif
#endif /* !Py_PGEN_H */
