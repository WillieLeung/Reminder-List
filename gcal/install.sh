#!/bin/bash

#run make from src
src_dir=$HOME/gcal/src
if [[ ! -d ${src_dir} ]]; then
	echo "Directory ${src_dir} does not exist"
	exit 1
else 
	cd ${src_dir}
	make
	echo "Compiled gcal"
fi

#create installation directory
install_dir=$HOME/.local/bin
if [[ ! -d ${install_dir} ]]; then
	mkdir ${install_dir}
	echo "Directory ${install_dir} created"
else
	echo "Directory ${install_dir} already exists"
fi

#copy executable to installation directory
executable=$HOME/gcal/src/gcal
if [[ ! -f ${executable} ]]; then
	echo "Executable ${executable} does not exist"
else
	cp ${executable} ${install_dir}
	echo "Installed gcal to ${install_dir}"
fi

#add installation directory to the $PATH variable
if [[ ":$PATH:" != *":${install_dir}:"* ]]; then
	echo "export PATH=${install_dir}:\$PATH" >> "$HOME/.bashrc"
	export PATH=$install_dir:$PATH 
	echo "Added ${install_dir} to PATH. Restart the terminal or run 'source ~/.bashrc' to apply changes."
else 
	echo "${install_dir} is already in PATH."
fi

echo "Installation Complete"
