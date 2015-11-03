/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package net.cofares;

import java.io.Serializable;
import javax.persistence.Query;
import javax.persistence.EntityNotFoundException;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.util.ArrayList;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import net.cofares.exceptions.NonexistentEntityException;
import net.cofares.exceptions.PreexistingEntityException;

/**
 *
 * @author pascalfares
 */
public class DepJpaController implements Serializable {

    public DepJpaController(EntityManagerFactory emf) {
        this.emf = emf;
    }
    private EntityManagerFactory emf = null;

    public EntityManager getEntityManager() {
        return emf.createEntityManager();
    }

    public void create(Dep dep) throws PreexistingEntityException, Exception {
        if (dep.getEmpList() == null) {
            dep.setEmpList(new ArrayList<Emp>());
        }
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            List<Emp> attachedEmpList = new ArrayList<Emp>();
            for (Emp empListEmpToAttach : dep.getEmpList()) {
                empListEmpToAttach = em.getReference(empListEmpToAttach.getClass(), empListEmpToAttach.getIdEmp());
                attachedEmpList.add(empListEmpToAttach);
            }
            dep.setEmpList(attachedEmpList);
            em.persist(dep);
            for (Emp empListEmp : dep.getEmpList()) {
                Dep oldIdDepOfEmpListEmp = empListEmp.getIdDep();
                empListEmp.setIdDep(dep);
                empListEmp = em.merge(empListEmp);
                if (oldIdDepOfEmpListEmp != null) {
                    oldIdDepOfEmpListEmp.getEmpList().remove(empListEmp);
                    oldIdDepOfEmpListEmp = em.merge(oldIdDepOfEmpListEmp);
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            if (findDep(dep.getIdDep()) != null) {
                throw new PreexistingEntityException("Dep " + dep + " already exists.", ex);
            }
            throw ex;
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public void edit(Dep dep) throws NonexistentEntityException, Exception {
        EntityManager em = null;
        try {
            em = getEntityManager();
            em.getTransaction().begin();
            Dep persistentDep = em.find(Dep.class, dep.getIdDep());
            List<Emp> empListOld = persistentDep.getEmpList();
            List<Emp> empListNew = dep.getEmpList();
            List<Emp> attachedEmpListNew = new ArrayList<Emp>();
            for (Emp empListNewEmpToAttach : empListNew) {
                empListNewEmpToAttach = em.getReference(empListNewEmpToAttach.getClass(), empListNewEmpToAttach.getIdEmp());
                attachedEmpListNew.add(empListNewEmpToAttach);
            }
            empListNew = attachedEmpListNew;
            dep.setEmpList(empListNew);
            dep = em.merge(dep);
            for (Emp empListOldEmp : empListOld) {
                if (!empListNew.contains(empListOldEmp)) {
                    empListOldEmp.setIdDep(null);
                    empListOldEmp = em.merge(empListOldEmp);
                }
            }
            for (Emp empListNewEmp : empListNew) {
                if (!empListOld.contains(empListNewEmp)) {
                    Dep oldIdDepOfEmpListNewEmp = empListNewEmp.getIdDep();
                    empListNewEmp.setIdDep(dep);
                    empListNewEmp = em.merge(empListNewEmp);
                    if (oldIdDepOfEmpListNewEmp != null && !oldIdDepOfEmpListNewEmp.equals(dep)) {
                        oldIdDepOfEmpListNewEmp.getEmpList().remove(empListNewEmp);
                        oldIdDepOfEmpListNewEmp = em.merge(oldIdDepOfEmpListNewEmp);
                    }
                }
            }
            em.getTransaction().commit();
        } catch (Exception ex) {
            String msg = ex.getLocalizedMessage();
            if (msg == null || msg.length() == 0) {
                Integer id = dep.getIdDep();
                if (findDep(id) == null) {
                    throw new NonexistentEntityException("The dep with id " + id + " no longer exists.");
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
            Dep dep;
            try {
                dep = em.getReference(Dep.class, id);
                dep.getIdDep();
            } catch (EntityNotFoundException enfe) {
                throw new NonexistentEntityException("The dep with id " + id + " no longer exists.", enfe);
            }
            List<Emp> empList = dep.getEmpList();
            for (Emp empListEmp : empList) {
                empListEmp.setIdDep(null);
                empListEmp = em.merge(empListEmp);
            }
            em.remove(dep);
            em.getTransaction().commit();
        } finally {
            if (em != null) {
                em.close();
            }
        }
    }

    public List<Dep> findDepEntities() {
        return findDepEntities(true, -1, -1);
    }

    public List<Dep> findDepEntities(int maxResults, int firstResult) {
        return findDepEntities(false, maxResults, firstResult);
    }

    private List<Dep> findDepEntities(boolean all, int maxResults, int firstResult) {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            cq.select(cq.from(Dep.class));
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

    public Dep findDep(Integer id) {
        EntityManager em = getEntityManager();
        try {
            return em.find(Dep.class, id);
        } finally {
            em.close();
        }
    }

    public int getDepCount() {
        EntityManager em = getEntityManager();
        try {
            CriteriaQuery cq = em.getCriteriaBuilder().createQuery();
            Root<Dep> rt = cq.from(Dep.class);
            cq.select(em.getCriteriaBuilder().count(rt));
            Query q = em.createQuery(cq);
            return ((Long) q.getSingleResult()).intValue();
        } finally {
            em.close();
        }
    }
    
}
