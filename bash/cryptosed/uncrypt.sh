#! /bin/bash

for (( i=0;i<10;i++ ));do
	for (( j=0;j<10;j++ ));do
		for (( k=0;k<10;k++ ));do
			for (( m=0;m<10;m++ ));do
			var="$i$j$k$m"
			` 7za e tex2html-test.tar.7z -p$var -y >/dev/null 2>&1 ` 
			if [ $? -ne 0 ];then 
				echo "$var - incorrect password"
			else
				echo "$var - correct password"
				exit 0
			fi				
			done	
		done
	done
done

