# Blaze

Mod for Geometry Dash that significantly speeds up loading times.

todo readme

feats:

* 30-40% faster savefile loading
* Up to 5-7x faster savefile saving
* ~200-400% faster game resource loading
* Parallelized audio engine loading (except on Android)
* 5-10% faster string creation
* Faster image decoding & image caching
* Mod can be safely uninstalled and your savefile will still load

Overall, game launches can be 2-3x faster, on my machine on average the speed goes up from ~2.9s to ~1.4s (38mb save, i5-13600k, no megahack, without globed asset preloading)

Note: all those numbers are on Windows. On other operating systems, the performance increase might not be that big.


## Credit

* [matcool](https://github.com/matcool) for [Fast Format](https://github.com/matcool/geode-mods/blob/main/fast-format/main.cpp) (i took the entire mod)
* [cgytrus](https://github.com/cgytrus) for [Algebra Dash](https://github.com/cgytrus/AlgebraDash) (Tracy integration taken from it, the rest of the optimizations were implemented by myself, even if the ideas are similar to ones in Config's mod)
