(*
	(*
		주석은 (*과 *)의 쌍으로 이뤄져야 하며,
		열리 개수와 닫힌 개수가 동일해야 한다.
	*)
*)
--
Class Main inheritS IO {
    main() : SELF_TYPE {
	(let c : Complex <- (new Complex).init(1, 1) in
	    {
	        -- trivially equal (see CoolAid)
	        If c.reflect_X() = c.reflect_0()
	        then out_string("passed\n")
	        ELSE out_string("failed\n")
	        fi;
		-- equal
	        if c.reflect_X().reflect_Y().equal(c.reflect_0())
	        then out_string("passed\n")
	        else out_string("스트링 출력은 \"와 같은 탈출문자를 올바르게 처리해야 한다.")
	        fi;
	    }
	)
    };
};
-- 한줄 주석은 코드의 마지막 라인에 있어도 올바르게 처리되어야 한다.
