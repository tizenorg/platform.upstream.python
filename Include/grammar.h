
/* Grammar interface */

#ifndef Py_GRAMMAR_H
#define Py_GRAMMAR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "bitset.h" /* Sigh... */

/* A label of an arc */

typedef struct {
    int		 lb_type;
    char	*lb_str;
} label;

#define EMPTY 0		/* Label number 0 is by definition the empty label */

/* A list of labels */

typedef struct {
    int		 ll_nlabels;
    label	*ll_label;
} labellist;

/* An arc from one state to another */

typedef struct {
    short	a_lbl;		/* Label of this arc */
    short	a_arrow;	/* State where this arc goes to */
} arc;

/* A state in a DFA */

typedef struct {
    int		 s_narcs;
    arc		*s_arc;		/* Array of arcs */
	
    /* Optional accelerators */
    int		 s_lower;	/* Lowest label index */
    int		 s_upper;	/* Highest label index */
    int		*s_accel;	/* Accelerator */
    int		 s_accept;	/* Nonzero for accepting state */
} state;

/* A DFA */

typedef struct {
    int		 d_type;	/* Non-terminal this represents */
    char	*d_name;	/* For printing */
    int		 d_initial;	/* Initial state */
    int		 d_nstates;
    state	*d_state;	/* Array of states */
    bitset	 d_first;
} dfa;

/* A grammar */

typedef struct {
    int		 g_ndfas;
    dfa		*g_dfa;		/* Array of DFAs */
    labellist	 g_ll;
    int		 g_start;	/* Start symbol of the grammar */
    int		 g_accel;	/* Set if accelerators present */
} grammar;

/* FUNCTIONS */

__attribute__ ((visibility ("default"))) grammar *newgrammar(int start);
__attribute__ ((visibility ("default"))) dfa *adddfa(grammar *g, int type, char *name);
__attribute__ ((visibility ("default"))) int addstate(dfa *d);
__attribute__ ((visibility ("default"))) void addarc(dfa *d, int from, int to, int lbl);
__attribute__ ((visibility ("default"))) dfa *PyGrammar_FindDFA(grammar *g, int type);

__attribute__ ((visibility ("default"))) int addlabel(labellist *ll, int type, char *str);
__attribute__ ((visibility ("default"))) int findlabel(labellist *ll, int type, char *str);
__attribute__ ((visibility ("default"))) char *PyGrammar_LabelRepr(label *lb);
__attribute__ ((visibility ("default"))) void translatelabels(grammar *g);

__attribute__ ((visibility ("default"))) void addfirstsets(grammar *g);

__attribute__ ((visibility ("default"))) void PyGrammar_AddAccelerators(grammar *g);
__attribute__ ((visibility ("default"))) void PyGrammar_RemoveAccelerators(grammar *);

__attribute__ ((visibility ("default"))) void printgrammar(grammar *g, FILE *fp);
__attribute__ ((visibility ("default"))) void printnonterminals(grammar *g, FILE *fp);

#ifdef __cplusplus
}
#endif
#endif /* !Py_GRAMMAR_H */
