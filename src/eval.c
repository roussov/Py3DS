#include "eval.h"
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "error.h"

static Value make_int(int v) {
    Value val;
    val.type = VAL_INT;
    val.int_val = v;
    return val;
}

static Value make_float(double v) {
    Value val;
    val.type = VAL_FLOAT;
    val.float_val = v;
    return val;
}

static Value make_none() {
    Value val;
    val.type = VAL_NONE;
    return val;
}

Value eval_node(ASTNode* node, Env* env, Error* err) {
    if (!node) {
        if (err) error_init(err, ERROR_INTERNAL, "AST node is NULL");
        return make_none();
    }

    switch (node->type) {
        case AST_INT_LITERAL:
            return make_int(node->int_value);

        case AST_FLOAT_LITERAL:
            return make_float(node->float_value);

        case AST_IDENT: {
            if (!node->ident_name) {
                if (err) error_init(err, ERROR_INTERNAL, "AST_IDENT node has null name");
                return make_none();
            }
            Value* val = env_get(env, node->ident_name);
            if (!val) {
                if (err) error_init(err, ERROR_NAME, "Undefined variable '%s'", node->ident_name);
                return make_none();
            }
            return *val;
        }

        case AST_BINARY_OP: {
            if (!node->binary.left || !node->binary.right || !node->binary.op) {
                if (err) error_init(err, ERROR_INTERNAL, "Malformed binary operation");
                return make_none();
            }

            Value left = eval_node(node->binary.left, env, err);
            if (err && err->type != ERROR_NONE) return make_none();
            Value right = eval_node(node->binary.right, env, err);
            if (err && err->type != ERROR_NONE) return make_none();

            if (strcmp(node->binary.op, "+") == 0) {
                if (left.type == VAL_INT && right.type == VAL_INT) {
                    return make_int(left.int_val + right.int_val);
                } else if ((left.type == VAL_FLOAT || left.type == VAL_INT) &&
                           (right.type == VAL_FLOAT || right.type == VAL_INT)) {
                    double l = (left.type == VAL_INT) ? (double)left.int_val : left.float_val;
                    double r = (right.type == VAL_INT) ? (double)right.int_val : right.float_val;
                    return make_float(l + r);
                } else {
                    if (err) error_init(err, ERROR_TYPE, "Type error for '+' operator");
                    return make_none();
                }
            }
            // Ajoute les autres opérateurs ici (-, *, /, etc.)

            if (err) error_init(err, ERROR_RUNTIME, "Unsupported operator '%s'", node->binary.op);
            return make_none();
        }

        default:
            if (err) error_init(err, ERROR_INTERNAL, "Unknown AST node type %d", node->type);
            return make_none();
    }
}
