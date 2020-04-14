struct PolyTerm {
    int coeff;
    int expo;
    struct PolyTerm *next;
};

int addPolyTerm(int coeff, int expo);
void displayPolynomial();
int evaluatePolynomial(int x);
void appendNode(struct PolyTerm *node);

extern struct PolyTerm *head;