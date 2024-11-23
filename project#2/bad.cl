(* no error *)
Class A InHerits B {
};

(* many errors *)
class C inherits B {
	a : Int <- 0;
	test1() : Int {
		Let i : int <- 1, j : string in i  -- int와 string은 대문자로 시작해야 함
	};
	test2(x:Int, y:String) : int { 1 };        -- 타입 int는 대문자로 시작해야 함
	test3() : Int {
		{
			x <- IF a THEN b ELSE c FI;
			if a then b fi;             -- else 부분이 없음
			a = Double + a;             -- Double은 타입명, 변수로 사용할 수 없음
			C = a + 5;                  -- C는 타입명, 변수로 사용할 수 없음
			a * 2;
			x.test2(x<-3+5, Y, Z);      -- Y, Z는 타입명, 인자로 사용할 수 없음
			x.test2(, y, z);            -- 누락된 인자
			x.test1();
		}
	};
	test4( : Int;                               -- 잘못된 메소드 형식
	test5(, y:String) : Int { y };              -- 누락된 형식 파라미터
};

(* error:  a is not a type identifier *)
Class D inherits a {                                -- a는 타입이 아님
};

(* error:  keyword inherits is misspelled *)
Class E inherts A {                                 -- 철자법 오류
};

(* error:  closing brace is missing *)
Class F inherits A {
;                                                   -- 오른쪽 괄호 없음

