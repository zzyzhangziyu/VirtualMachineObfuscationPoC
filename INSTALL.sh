#!/bin/bash

cat << "EOF"
 __   ____  __ ___ ___  ___ _____ ___ ___ _____                                                 
 \ \ / /  \/  | _ \ _ \/ _ \_   _| __/ __|_   _|                                                
  \ V /| |\/| |  _/   / (_) || | | _| (__  | |                                                  
   \_/ |_|  |_|_| |_|_\\___/ |_| |___\___| |_|                _                            _    
  __| |_____ _____| |___ _ __ _ __  ___ _ _| |_   ___ _ ___ _(_)_ _ ___ _ _  _ __  ___ _ _| |_  
 / _` / -_) V / -_) / _ \ '_ \ '  \/ -_) ' \  _| / -_) ' \ V / | '_/ _ \ ' \| '  \/ -_) ' \  _| 
 \__,_\___|\_/\___|_\___/ .__/_|_|_\___|_||_\__| \___|_||_\_/|_|_| \___/_||_|_|_|_\___|_||_\__| 
          _             |_|         _        _ _                                                
  ___ ___| |_ _  _ _ __  (_)_ _  __| |_ __ _| | |___ _ _                                        
 (_-</ -_)  _| || | '_ \ | | ' \(_-<  _/ _` | | / -_) '_|                                       
 /__/\___|\__|\_,_| .__/ |_|_||_/__/\__\__,_|_|_\___|_|                                         
                  |_|                                                                           
EOF
echo "version 0.2.200921.2026"
echo "#####################################"

echo ""
echo "Write path to deploy"
read pathToInstall

# #####################################
# ############## STAGE 1 ##############
echo "STAGE 1 - check if require programs exist"
if ! [ -x "$(command -v python3)" ];
then
        echo "  WARNING: python3 could not be found"
else
        echo "  python3 installed - check"
fi

if ! [ -x "$(command -v make)" ];
then
        echo "  WARNING: make could not be found"
else
        echo "  make installed - check"
fi

if ! [ -x "$(command -v g++)" ];
then
        echo "  WARNING: g++ could not be found"
else
        echo "  g++ installed - check"
fi

if ! [ -x "$(command -v nasm)" ];
then
        echo "  WARNING: nasm could not be found"
else
        echo "  nasm installed - check"
fi
# #####################################


echo "\e[1;31m!!!! NOT READY !!!!\e[0m"

# e.g.
# make -C ./Debugger build
# make -C ./Debugger clean
