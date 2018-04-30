extern crate rand;

use rand::Rng;

#[derive(Debug)]
pub struct Msweeper {
    width: usize,
    height: usize,
    bnum: usize,
    map: Vec<(bool, bool)>
}

impl Msweeper {
    pub fn new(w: usize, h: usize, b: usize) -> Msweeper {
        let mut rng = rand::thread_rng();
        let mut map = vec![(false, false); w * h];

        for i in 0..b {
            map[i].1 = true;
        }

        rng.shuffle(&mut map);

        Msweeper { width: w, height: h, bnum: b, map: map }
    }

    pub fn get_width(&self) -> usize {
        self.width
    }

    pub fn get_height(&self) -> usize {
        self.height
    }

    pub fn at(&self, x: usize, y: usize) -> Result<(bool, i32), String> {
        if !(x < self.width && y < self.height) { 
            return Err("index out of bounds.".to_string()); 
        }

        let mut c = 0;
        for dy in -1..2 {
            for dx in -1..2 {
                if !self.b_check(x, y, dx, dy) { continue }
                let pos = (y as i32 + dy) as usize * self.width + (x as i32 + dx) as usize;
                if self.map[pos].1 { c = c + 1; }
            }
        }
        Ok((self.map[y * self.width + x].0, c))
    }

    pub fn is_gameend(&self) -> bool {
        let mut end = true;
        for i in 0..(self.width * self.height) {
            let (opened, bombed) = self.map[i];
            if opened && bombed { break; }
            if !opened && !bombed { end = false; break; }
        }
        end
    }

    pub fn open(&mut self, x: usize, y: usize) -> Result<(), String> {
        if !(x < self.width && y < self.height) { 
            return Err("index out of bounds.".to_string()); 
        }

        self.map[y * self.width + x].0 = true;

        let num = match self.at(x, y) {
            Ok((_, num)) => num,
            Err(_) => return Err("internal processing error.".to_string())
        };

        if num == 0 {
            for dy in -1..2 {
                for dx in -1..2 {
                    if !self.b_check(x, y, dx, dy) { continue }
                    let (cx, cy) = ((x as i32 + dx) as usize, (y as i32 + dy) as usize);
                    match self.at(cx, cy) {
                        Ok((opened, _)) => if !opened { 
                            match self.open(cx, cy) {
                                Ok(_) => (),
                                Err(_) => return Err("internal processing error.".to_string())
                            }
                        },
                        Err(_) => return Err("internal processing error.".to_string())
                    }
                }
            }
        }
        Ok(())
    }

    fn b_check(&self, x: usize, y: usize, dx: i32, dy: i32) -> bool {
        !(dx == 0 && dy == 0) 
            && !(x ==0 && dx == -1) 
            && !(y == 0 && dy == -1) 
            && !(x + 1 == self.width && dx == 1) 
            && !(y + 1 == self.height && dy == 1)
    }
}
