#ifndef Py_AST_H
#define Py_AST_H
#ifdef __cplusplus
extern "C" {
#endif

__attribute__ ((visibility ("default"))) PyAPI_FUNC(mod_ty) PyAST_FromNode(const node *, PyCompilerFlags *flags,
				  const char *, PyArena *);

#ifdef __cplusplus
}
#endif
#endif /* !Py_AST_H */
