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
        self.width
    }

    pub fn at(&self, x: usize, y: usize) -> i32 {
        let c = 0;
        for dy in -1..2 {
            for dx in -1..2 {
                if x == 0 && dx == -1 { continue }
                if y == 0 && dy == -1 { continue }
                if x + 1 == self.width && dy == 1 { continue }
                if y + 1 == self.height && dy == 1 { continue }
            }
        }
        if self.map[y * self.width + x].0 { c } else { -1 }
    }
}
