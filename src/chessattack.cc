char ispawn = theGrid.at(old_r).at(static_cast<int>(old_c))->get_name();
if (ispawn == 'P' && (old_r == new_r + 1) && (static_cast<int>(old_c) == static_cast<int>(new_c) - 1 || static_cast<int>(old_c) == static_cast<int>(new_c) + 1)){

    if (colour == 'B'){
        
        // check my colour
        throw InvalidMove{};
    } else {
        char new_colour = theGrid.at(old_r).at(static_cast<int>(old_c))->get_colour();
        
        if (new_colour == 'W'){
            
            // check new colour
            throw InvalidMove{};
        } else if (theGrid.at(new_r).at(static_cast<int>(new_c)) == nullptr) {
            
            // check new piece
            throw InvalidMove{};
        } else {
            
            // move
            theGrid.at(old_r).at(static_cast<int>(old_c)).swap(theGrid.at(new_r).at(static_cast<int>(new_c)));
            theGrid.at(old_r).at(static_cast<int>(old_c)).reset();
			theGrid.at(old_r).at(static_cast<int>(old_c)) = nullptr;
        }
    }
    
} else if (ispawn == 'p' && (old_r == new_r - 1) && (static_cast<int>(old_c) == static_cast<int>(new_c) - 1 || static_cast<int>(old_c) == static_cast<int>(new_c) + 1)){
    
    if (colour == 'W'){
        
        // check my colour
        throw InvalidMove{};
    } else {
        char new_colour = theGrid.at(old_r).at(static_cast<int>(old_c))->get_colour();
        
        if (new_colour == 'B'){
            
            // check new colour
            throw InvalidMove{};
        } else if (theGrid.at(new_r).at(static_cast<int>(new_c)) == nullptr) {
            
            // check new piece
            throw InvalidMove{};
        } else {
            
            // move
            theGrid.at(old_r).at(static_cast<int>(old_c)).swap(theGrid.at(new_r).at(static_cast<int>(new_c)));
            theGrid.at(old_r).at(static_cast<int>(old_c)).reset();
			theGrid.at(old_r).at(static_cast<int>(old_c)) = nullptr;
        }
    }  
    
}