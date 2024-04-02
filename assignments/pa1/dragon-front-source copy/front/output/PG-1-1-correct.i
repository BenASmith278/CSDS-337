L1:	t1 = 0 * 4
	a [ t1 ] = 1
L3:	t2 = 1 * 4
	a [ t2 ] = 3
L4:	t3 = 2 * 4
	a [ t3 ] = 2
L5:	t4 = 3 * 4
	a [ t4 ] = 4
L6:	i = 0
L7:	iffalse i < 3 goto L2
	j = 0
L9:	t5 = 3 - i
	iffalse j < t5 goto L8
	t6 = j * 4
	t7 = a [ t6 ]
	t8 = j + 1
	t9 = t8 * 4
	t10 = a [ t9 ]
	iffalse t7 > t10 goto L10
L11:	t11 = j * 4
	temp = a [ t11 ]
L12:	t12 = j * 4
	t13 = j + 1
	t14 = t13 * 4
	t15 = a [ t14 ]
	a [ t12 ] = t15
L13:	t16 = j + 1
	t17 = t16 * 4
	a [ t17 ] = temp
L10:	j = j + 1
	goto L9
L8:	i = i + 1
	goto L7
L2:
