# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_pipes.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:47 by jmartel           #+#    #+#              #
#    Updated: 2019/06/20 15:52:38 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Pipes tests
launch "Pipes simple"
	test_launch "ls -a"
	test_launch "ls -a | wc"
	test_launch "ls -a | wc | wc"
	test_launch "ls -a | wc | wc ; ls -a "
	test_launch "echo mdr | wc | cat -e | wc"

launch "Pipes on Builtins"
	test_launch 'pwd' 'cd ../../.. | echo lol | exit | echo lol' 'pwd'
	test_launch 'exit | exit'
	test_launch 'exit | true | exit'
	test_launch 'yes | head -c1'
	test_launch 'cat | cat | wc'
	test_launch 'emacs | emacs'
	test_launch 
	test_launch 
	test_launch 
finish
