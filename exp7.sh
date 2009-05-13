#!/usr/bin/bash
export NO_RES=1; export RAW=1

for n in 200 250; do
	for r in 0.07 0.08 0.09 0.10 0.11 0.12 0.13 0.14 0.15 0.16 0.17 0.18 0.19 0.20 0.21; do
		NUM_RUNS=7 ./p $r $n
	done
done
for n in 300 350; do
	for r in 0.06 0.07 0.08 0.09 0.10 0.11 0.12 0.13 0.14 0.15 0.16 0.17 0.18 0.19 0.20; do
		NUM_RUNS=6 ./p $r $n
	done
done
for n in 400 450; do
	for r in 0.05 0.06 0.07 0.08 0.09 0.10 0.11 0.12 0.13 0.14 0.15 0.16 0.17 0.18 0.19; do
		NUM_RUNS=5 ./p $r $n
	done
done
for n in 500 550; do
	for r in 0.04 0.05 0.06 0.07 0.08 0.09 0.10 0.11 0.12 0.13 0.14 0.15 0.16 0.17 0.18; do
		NUM_RUNS=4 ./p $r $n
	done
done
for n in 600 650; do
	for r in 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.10 0.11 0.12 0.13 0.14 0.15 0.16 0.17; do
		NUM_RUNS=3 ./p $r $n
	done
done
for n in 700; do
	for r in 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.10 0.11 0.12 0.13 0.14 0.15 0.16; do
		NUM_RUNS=2 ./p $r $n
	done
done

