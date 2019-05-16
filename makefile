libs=./knn/knn.c
knn=./knn/main.c
treinamento=./data/treinamento.txt
teste=./data/teste.txt









run-knn: knn
	./knn $(treinamento) $(teste)
knn:
	gcc $(libs) $(knn) -o knn

