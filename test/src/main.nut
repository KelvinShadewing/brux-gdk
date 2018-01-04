::main <- function(){
				setFPS(30);
				setResolution(320, 180);

				quit <- false;
				while(!quit){
								if(keyPress(k_escape)) quit = true;
				};
};
