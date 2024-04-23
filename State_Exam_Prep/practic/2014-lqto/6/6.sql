USE pc;



-- 2014 lqto zad.6.1

--(moe resh)
--SELECT DISTINCT p.maker
--FROM product as p
--JOIN pc as p_c on p.model=p_c.model
--and p.maker IN (SELECT DISTINCT p.maker
--				FROM product as p
--				JOIN laptop as l on p.model=l.model) 

--a) v 
--SELECT distinct maker
--from product 
--where product.type='PC'
--and maker in (select maker
--			  from product JOIN laptop on product.model=laptop.model)
--b) x, slojili sme alias a ne go izpolzvame,error
--c) x , iskame sechenie a ne obedinenie
--d) x, iskame sechenie a ne obedinenie




-- 2014 lqto zad.6.2

--moe resh

--select *
--from product
--order by maker

--SELECT p.maker,COUNT(pr.code)
--				FROM product as p
--				LEFT JOIN printer as pr on p.model=pr.model
--				GROUP BY p.maker
--				HAVING COUNT(pr.code) <= 3

--SELECT l.code,l.model,l.screen,p.maker
--FROM product as p
--JOIN laptop as l on p.model=l.model
--WHERE p.maker IN
--				(SELECT p.maker
--				FROM product as p
--				LEFT JOIN printer as pr on p.model=pr.model
--				GROUP BY p.maker
--				HAVING COUNT(pr.code) <= 3)


--a) x, syntax error
--b) x, syntax error having without group by
--c) x , having > 3 , a nie iskame <3
--d ) v
--SELECT l.code ,l.model , l.screen,p.maker
--FROM laptop l
--JOIN product p on l.model=p.model
--where p.maker in ( select maker
--				  from product 
--				  where type='Printer'
--				  group by maker
--				  having count(*) <=3)


--e) x, group by l.code instead of maker i group by trqbva da sudurja vsichko v selecta, obratnoto ne vinagi e nujno
--SELECT l.code, l.model, l.screen
--FROM Product p LEFT JOIN Laptop l ON p.model = l.model 
--LEFT JOIN Printer on p.model = Printer.model
--GROUP BY l.code
--HAVING COUNT(DISTINCT Printer.code) <= 3;