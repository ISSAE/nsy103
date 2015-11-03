/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package net.cofares;

import java.io.Serializable;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Query;
import javax.persistence.EntityNotFoundException;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import net.cofares.exceptions.NonexistentEntityException;
import net.cofares.exceptions.PreexistingEntityException;

/**
 *
 * @author pascalfares
 */
public class EmpJpaController implements Serializable {

    public EmpJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(Emp emp) throws PreexistingEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Dep idDep = emp.getIdDep();
            if (idDep != null) {
                idDep = em.getReference(idDep.getClass(), idDep.getIdDep());
                emp.setIdDep(idDep);
            }
            em.persist(emp);
            if (idDep != null) {
                idDep.getEmpList().add(emp);
                idDep = em.merge(idDep);
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findEmp(emp.getIdEmp()) != null) {
                throw new PreexistingEntityException("Emp " + emp + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(Emp emp) throws NonexistentEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Emp persistentEmp = em.find(Emp.class, emp.getIdEmp());
            Dep idDepOld = persistentEmp.getIdDep();
            Dep idDepNew = emp.getIdDep();
            if (idDepNew != null) {
                idDepNew = em.getReference(idDepNew.getClass(), idDepNew.getIdDep());
                emp.setIdDep(idDepNew);
            }
            emp = em.merge(emp);
            if (idDepOld != null && !idDepOld.equals(idDepNew)) {
                idDepOld.getEmpList().remove(emp);
                idDepOld = em.merge(idDepOld);
            }
            if (idDepNew != null && !idDepNew.equals(idDepOld)) {
                idDepNew.getEmpList().add(emp);
                idDepNew = em.merge(idDepNew);
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                Integer id = emp.getIdEmp();
                if (findEmp(id) == null) {
                    throw new NonexistentEntityException("The emp with id " + id + " no longer exists.");
                }
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void destroy(Integer id) throws NonexistentEntityException {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Emp emp;
            try {
                emp = em.getReference(Emp.class, id);
                emp.getIdEmp();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The emp with id " + id + " no longer exists.", enfe);
            }
            Dep idDep = emp.getIdDep();
            if (idDep != null) {
                idDep.getEmpList().remove(emp);
                idDep = em.merge(idDep);
            }
            em.remove(emp);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<Emp> findEmpEntities() {
        return findEmpEntities(true, -1, -1);
    }

    public List<Emp> findEmpEntities(int maxResults, int firstResult) {
        return findEmpEntities(false, maxResults, firstResult);
    }

    private List<Emp> findEmpEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(Emp.class));
            Query q = em.createQuery(cq);
            if (!all) {
                q.setMaxResults(maxResults);
                q.setFirstResult(firstResult);
            }
            return q.getResultList();
        } finally {
            em.close();
        }
    }

    public Emp findEmp(Integer id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(Emp.class, id);
        } finally {
            em.close();
        }
    }

    public int getEmpCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<Emp> rt = cq.from(Emp.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }
    
}
