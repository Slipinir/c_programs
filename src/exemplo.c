typedef int (*fx)(int, char);

int outra_funcao(int i, char c) {
    //
}

int funcao (int i, char c, funcao fx) {
    fx(i, c);
}

void main() {
    funcao(8, "c", &outra_funcao);
}
