package inter;

import symbols.*;

public class For extends Stmt {
    Stmt stmt1, stmt2, stmts;
    Expr expr;

    public For() {
        stmt1 = null;
        stmt2 = null;
        stmts = null;
        expr = null;
    }

    public void init(Stmt s1, Expr e, Stmt s2, Stmt ss) {
        stmt1 = s1;
        stmt2 = s2;
        stmts = ss;
        expr = e;
        if (expr != null && expr.type != Type.Bool)
            expr.error("boolean required in for");
    }

    public void gen(int b, int a) {
        after = a; // save label a
        // do statement 1
        int l1 = newlabel();
        stmt1.gen(b, l1);

        emitlabel(l1); // label for loop beginning
        expr.jumping(0, a);

        // do statements
        int l2 = newlabel();
        stmts.gen(l1, l2);
        emitlabel(l2);

        // do statement 2
        stmt2.gen(l2, l1);
        // goto expr
        emit("goto L" + l1);
    }
}
