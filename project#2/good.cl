(* 이 프로그램은 COOL 문법이 맞는지 검사하기 위한 것으로 의미적으로는 올바르지 않다. *)
class A {};
class B inherits C {};
class C inherits A {
    x:Int <- ~35;
    y:B <- new B;
    z:Str <- "hello";
};
class D inherits C {
    x:Int <- a+b*c;
    y:C <- new C;
    foo():Bool { false };
    bar(x:Int, y:Int, z:Int):Bool { (x+y*z-y) <= ((((z-y)))) };
};
class E {
    bar():Bool {
        {
            dummy@Int.foo(1,2,3);
            dummy.foo(a,b,c);
            foo(x,y,z);
            bar();
        }
    };
};
class F {
    foo():Bool {
        {
            if if x then y <- 1 else z fi then a else c fi;
            while x < 9 loop {
                if x = 3 then y<-5 else y<-7 fi;
                z <- x * y;
            } pool;
        }
    };
};
class G {
    bar():Bool {
        let x:Int <- 1, y:D <- new D, z:Bool in y.foo(1,2,3)+3
    };
};
class H {
    foo():Int {
        case a+b*c of
            x:Int => a;
            y:Int => a+b;
            z:Int => a+b*c;
        esac
    };
};
