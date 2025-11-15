#include "hw7.h"
//Christopher Guayara ID: 112881441


void push(char* stack, int* top, char ch){
    stack[++(*top)] = ch; 
}

char pop(char* stack, int* top){
    return stack[(*top)--];
}

char peek(char *stack , int topnum) {
    return stack[topnum];
}

int prec(char ch){
    if (ch == '\'')
        return 3;
    else if ( ch == '*')
        return 2;
    else if (ch == '+') 
        return 1;
    else return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '*' || ch == '\'');
}

matrix_sf* addOrMul(matrix_sf *first, matrix_sf *sec, char op){
    if( op == '+') return add_mats_sf(first, sec);
    else return mult_mats_sf(first, sec);
}

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    if (root == NULL){
        bst_sf* newBst = malloc(sizeof(bst_sf));
        newBst->mat = mat;
        newBst->left_child = NULL;
        newBst->right_child = NULL;
        return newBst;
    }

    if(mat->name < root->mat-> name)
        root->left_child = insert_bst_sf(mat, root->left_child);

    else {
        root->right_child = insert_bst_sf(mat, root->right_child);
    }

    
    return root;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    if (root == NULL){
        return NULL;
    }

    if(root->mat->name == name) return root->mat;
    if(root->mat->name < name)
        root->left_child = find_bst_sf(name, root->left_child);

    else {
        root->right_child = find_bst_sf(name, root->right_child);
    }

}

void free_bst_sf(bst_sf *root) {
    //base case 
    if(root == NULL) return;

    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);

    free(root->mat);
    free(root);
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    unsigned int rowLen = mat1->num_rows;
    unsigned int colLen = mat1->num_cols;
    unsigned int totalLen = rowLen * colLen;

    matrix_sf* res = malloc(sizeof(matrix_sf) + totalLen *sizeof(int));
    res->num_rows = rowLen;
    res->num_cols = colLen;

    for (int i = 0 ; i < rowLen ; i++) {
        for(int j = 0; j< colLen; j++) {
            res->values[i * colLen + j] = mat1->values[i* colLen +j] + mat2->values[i*colLen + j];

        }
    }
    return res;
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
	unsigned int rowLen = mat1->num_rows;
	unsigned int colLen = mat2->num_cols;
	unsigned int totalLen = rowLen * totalLen;
	matrix_sf *res = malloc(sizeof(matrix_sf) + totalLen*sizeof(int));
	res->num_rows = rowLen;
	res->num_cols = colLen;
    res-> name = ' ';
	for (int i = 0; i < rowLen; i++) {
		for(int j = 0; j < colLen; j++){
			for(int k = 0; k < mat1->num_cols; k++ )
			res->values[i * colLen + j] += mat1->values[i *mat1->num_cols + k] * mat2->values[k * mat2->num_cols + j];
		}
	}
	return res;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
	unsigned int rowLen = mat->num_cols;
	unsigned int colLen = mat->num_rows;
	unsigned int totalLen = rowLen * totalLen;

	matrix_sf *res = malloc(sizeof(matrix_sf) + totalLen*sizeof(int));
	res->num_rows = rowLen;
	res->num_cols = colLen;
    res->name = ' ';

	/*
	 * basically we are looking to flip ij to ji, we must have some sort of temp value as it seems to me
	 * 
     */
    for (int i = 0 ;i < rowLen; i++){
        for( int j = 0 ; j < colLen; j++){
               res->values[j * row + i] = mat->values[i * mat->num_cols + j];
        }
    }


    return res;
}
matrix_sf* create_matrix_sf(char name, const char *expr) {
    unsigned int rows = 0;
    unsigned int cols = 0;
    int len = strlen(expr);
    int state = 0;
    int read = 0;

    int numberseen = 0;

    matrix_sf* newMat;
    
    int currR = 0, currC = 0;

    int currNum = 0;


    for(int i = 0; i < len; i++ ){
        char curr = expr[i];

        if(isspace(curr)) continue;
        //set matrices

        if (state == 0) {
            if(isdigit(curr)){
                currNum = currNum * 10 +(curr - '0');
                read = 1;
            }
            
            else {
                if (read) {
                    if (numberseen == 0) rows = currNum;
                    else if(numberseen == 1 ) cols = currNum;

                    numberseen ++;
                    currNum = 0;
                    read = 0;
                }
                if (curr == '[') {
                    newMat = malloc(sizeof(matrix_sf) +rows*cols*sizeof(int));
                    newMat->name = name;
                    newMat->num_rows = rows;
                    newMat->num_cols = cols;
                    state = 1;

                }
            }
        }
        else if (state == 1) {
            
            if(digit(curr)) {
                currNum = currNum * 10 + (curr -'0');
                read = 1;
            }else{
                if(read) {
                    newMat->values[currR * cols +currC] = currNum;
                    currC++;

                    if(currC == cols) {
                        currC = 0;
                        currR++;
                    }
                    currNum = 0;
                    read = 0;
                }

                if (curr == ']') break;
            }
        }
    }

    

	
    return newMat;
}


char* infix2postfix_sf(char *infix) {
    int len = strlen(infix);
    char stack[100];
    int top = -1;
    char *postfix = malloc(len+1);
    int index = 0;

    for (int i = 0; i < len; i++) {
        char ch = infix[i];
        if(isspace((unsigned char)ch)) continue;
        
        if(isOperator) {
            postfix[index++] = ch;
            continue;
        }

        if (ch == '\'') {
            while(top >= 0 && prec(stack[top]) >= prec[ch]){
                postfix[index++] = pop(stack, &top);
                continue;
            }
            push(stack , &top, ch);
            continue;
        }

        if (ch == '(') {
            push(stack, &top, ch);
            continue;

        }

        if( ch == ')') {
            while(top >= 0 && stack[top] != '(') {
                postfix[index++] = pop(stack, &top);
            }
            if(top >= 0 ) pop(stack, &top);
            continue;
        }

        if (isOperator(ch)) {
            while(top >= 0 && prec(stack[top] >= prec(ch))) {
                postfix[index++] = pop(stack, &top);
            }
            push(stack, &top, ch);
            
        }

    }

    while ( top >= 0) {
        postfix[index++] = pop(stack, &top);
    }
    postfix[index] = '\0';
    return postfix;
}

matrix_sf* evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    char *post = infix2postfix_sf(expr);
    matrix_sf* mats[100];
    matrix_sf *res;
    
    int top = -1;
    
    
    for(int i = 0; post[i] != '\0' ; i++) {
        char ch = post[i];
        if(isspace(ch)) continue;

        if(ch >= 'A' && ch <= 'Z') {
            matrix_sf *mat = find_bst_sf(ch , root);

            stack[++top] = mat;
        }
        else if (ch == '\'') {
            matrix_sf *mat = mats[top--];
            matrix_sf *trans = transpose_mat_sf(mat);

            if(mat->name < 'A' || mat->name > 'Z' ) free(mat);
            mats[++top] = trans;

        }
        else if(isOperator(ch)) {
            matrix_sf *L = mats[top--];
            matrix_sf *R = mats[top--];
            

            if(ch == '+') res = add_mats_sf(L,R);
            else res = mult_mats_sf(L, R);

            if(L->name > 'A' || L->name < 'Z' ) free(L);
            if(R->name > 'A' || R->name < 'Z') free(R);
            mats[++top] = res;
        }
    }
    matrix_sf *result = mats[top];
    res->name = name;
    free(post);
    
    return res;
}

matrix_sf *execute_script_sf(char *filename) {

    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    bst_sf *root = NULL;
    char *line = NULL;
    size_t maxLen = MAX_LINE_LEN;

    matrix_sf *lastMat = NULL;

    while(getline(&line , &maxLen, file) != -1){

        int skip = 1;

        for(int i = 0; line[i] != '\0'; i++) {
            if(!isspace((unsigned int) line[i])) {
                skip = 0;
                break;
            }
        }
        
            if (skip) continue;

            int j = 0;

            while(isspace(((unsigned int) line[j ]))) j++;

            if(line[j] >= 'A' && line[j]) j++;

            if(line[j] >= 'A' && line[j] <= 'Z'){
                char name = line[j++];

                while(isspace((unsigned int) line[j])) j++;

                if(line[j] == '=') j++;

                while (isspace((unsigned int)line[j])) j++;

                char *expr = line + j;
                if(strchr(expr, '[') != NULL){
                    lastMat = create_matrix_sf(name, expr);

                }
                else {
                    lastMat = evaluate_expr_sf(name, expr, root);
                }

                root = insert_bst_sf(lastMat, root);
            }
        }
        free(line);
        fclose(file);
        free_bst_sf(root);

        return lastMat;


}




// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}

// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}



int main(int argc, char *argv[]){

    if (argc < 2 ){
        printf("Using: %s <file>\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];

    matrix_sf *lastMat = execute_script_sf(filename);
    return 0;
}
