# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_random.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/06/10 11:24:22 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Shell"
	launch "Random"
	test 'mkdir test123 ; cd test123 ; ls -a ; ls | cat | wc -c > fifi ; cat fifi ; cd .. ; rm -r test123'
finish