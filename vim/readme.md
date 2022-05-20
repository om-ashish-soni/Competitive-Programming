# vim-configuration

    set number

    set relativenumber

    set tabstop=4

    set shiftwidth=4

    set autoindent

    set mouse=a

    colorscheme default

    autocmd vimEnter *.cpp map <F8> :w <CR> :!clear ; g++ --std=c++17 %;if[-f] a.out];time ./a.out; rm a.out; <CR>

  
# Note : 
  ## just paste above code to .vimrc file.
  ## do below commands : 
  
      vi ~/.vimrc

      //then write above code of vim-configuration

      press f8 to compile and run the code
  
## vim is the one of the best suitable editor for competitive programming
  
