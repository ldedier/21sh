# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_bultins.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/05/21 16:00:41 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##	Builtin tests
##		Echo :
launch "Echo (builtin)"
	test "echo -n okalm"
	test "echo -n "
	test "echo"
	test "echo okalm"
	test 'echo $env'
	test 'echo $TERM'
	test 'echo $poasd'
	test 'echo $TERM $PATH'
	test 'echo -n $TERM $PATH'
finish